#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int compare(const void *data1, const void *data2);
bool has_cycle_helper(int index, bool visited[]);
bool has_cycle(int index);
bool is_source(int index);
int get_source();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int ii = 0;
    for (ii = 0; ii < candidate_count; ii++)
    {
        if (!strcmp(candidates[ii], name))
        {
            ranks[rank] = ii;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int ii = 0, jj = 0;
    for (ii = 0; ii < candidate_count; ii++)
    {
        for (jj = ii + 1; jj < candidate_count; jj++)
        {
            preferences[ranks[ii]][ranks[jj]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int ii = 0, jj = 0;
    pair_count = 0;
    for (ii = 0; ii < candidate_count; ii++)
    {
        for (jj = 0; jj < candidate_count; jj++)
        {
            if (preferences[ii][jj] > preferences[jj][ii])
            {
                pair p;
                p.winner = ii;
                p.loser = jj;
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }
    return;
}

int compare(const void *data1, const void *data2)
{
    pair f = *((pair *)data1);
    pair s = *((pair *)data2);
    int first = preferences[f.winner][f.loser] - preferences[f.loser][f.winner];
    int second = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    return second - first;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare);
    return;
}

bool has_cycle_helper(int index, bool visited[])
{
    int ii = 0;
    if (visited[index])
    {
        return true;
    }
    visited[index] = true;
    for (ii = 0; ii < candidate_count; ii++)
    {
        if (locked[index][ii] && (has_cycle_helper(ii, visited)))
        {
            return true;
        }
    }
    return false;
}

bool has_cycle(int index)
{
    int ii = 0;
    bool visited[candidate_count];
    for (ii = 0; ii < candidate_count; ii++)
    {
        visited[ii] = false;
    }
    return has_cycle_helper(index, visited);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int ii = 0;
    for (ii = 0; ii < pair_count; ii++)
    {
        locked[pairs[ii].winner][pairs[ii].loser] = true;
        if (has_cycle(ii))
        {
            locked[pairs[ii].winner][pairs[ii].loser] = false;
        }
    }
    return;
}

bool is_source(int index)
{
    int ii = 0;
    for (ii = 0; ii < candidate_count; ii++)
    {
        if (locked[ii][index])
        {
            return false;
        }
    }
    return true;
}

int get_source()
{
    int ii = 0;
    for (ii = 0; ii < candidate_count; ii++)
    {
        if (is_source(ii))
        {
            return ii;
        }
    }
    return -1;
}
// Print the winner of the election
void print_winner(void)
{
    int index = get_source();
    if (index != -1)
    {
        printf("%s\n", candidates[index]);
    }
    return;
}

