#include <stdio.h>
#include <string.h>

int checkSingularity(char *key);
int getKeys(char *key, int *upperKey, int *lowerKey);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    else if (checkSingularity(argv[1]))
    {
        printf("Key must contain 26 unique characters.\n");
        return 1;
    }
    int upperKey[26];
    int lowerKey[26];
    char text[100];
    int ii = 0;

    if (getKeys(argv[1], upperKey, lowerKey))
    {
        return 1;
    }

    printf("plaintext: ");
    scanf("%[^\n]", text);
    while (text[ii] != '\0')
    {
        if ((int)text[ii] >= 65 && (int)text[ii] <= 90)
        {
            text[ii] = (char)upperKey[(int)text[ii] - 65];
        }
        else if ((int)text[ii] >= 97 && (int)text[ii] <= 122)
        {
            text[ii] = (char)lowerKey[(int)text[ii] - 97];
        }
        ii++;
    }

    printf("ciphertext: %s\n", text);
    return 0;

}

int checkSingularity(char *key)
{
    int ii = 0, jj = 0;
    for (ii = 0; ii < 26; ii++)
    {
        for (jj = 0; jj < 26; jj++)
        {
            if (key[ii] == key[jj] && ii != jj)
            {
                return -1;
            }
        }
    }
    return 0;
}

int getKeys(char *key, int *upperKey, int *lowerKey)
{
    int ii = 0;
    for (ii = 0; ii < 26; ii++)
    {
        if (((int)key[ii] >= 65 && (int)key[ii] <= 90))
        {
            upperKey[ii] = (int)key[ii];
            lowerKey[ii] = (int)key[ii] + 32;
        }
        else if (((int)key[ii] >= 97 && (int)key[ii] <= 122))
        {
            lowerKey[ii] = (int)key[ii];
            upperKey[ii] = (int)key[ii] - 32;
        }
        else
        {
            printf("Key must have only alphabetic characters.\n");
            return -1;
        }
    }
    return 0;
}