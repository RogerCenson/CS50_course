// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int L = 27;
const unsigned int N = L * L * L;
int words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = 0;
    char tmpWord[LENGTH + 1];
    int length = strlen(word);
    for (int ii = 0; ii <= length; ii++)
    {
        tmpWord[ii] = tolower(word[ii]);
    }
    index = hash(tmpWord);
    node *helper = table[index];

    while (true)
    {
        if (helper == NULL)
        {
            return false;
        }
        else if (!(strcasecmp(helper->word, word)))
        {
            return true;
        }
        else
        {
            helper=helper->next;
        }
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word);
    int index = 0, ii = 0;
    if (length < 1)
    {
        return 0;
    }
    else if (length >= 3)
    {
        index = 0;
        for (ii = 0; ii < ((length > 3) ? 3 : length); ii++)
        {
            if (isalpha(word[ii]))
            {
                index = index + ((int)word[ii] - 97) * pow(L, 2 - ii);
            }
            else
            {
                index = index + 27 * pow(L, 2 - ii);
            }
        }
    }
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int count = 0, c = 0;
    unsigned int index;
    char word[LENGTH + 1];
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }
    while (fscanf(inptr, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        index = hash(word);

        n->next = table[index];

        table[index] = n;

        words++;
    }
	fclose(inptr);
    return true;
    }

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
     // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
        // If cursor is not NULL, free
        while (cursor)
        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }
        // If cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}