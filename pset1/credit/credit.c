#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum
{
    amex = 1,
    mastercard,
    visa,
    invalid
};

void printfType(int type);
void getType(char *credicard_str, int *type, int digits);
int getdigitss(long count_numer);

int main(void)
{
    long credicard = 0;
    char *credicard_str;
    int type = 0;
    int digits = 0, count_numer = 0;
    int ret = 0, ii = 0, is_multiply = 0;
    while (1)
    {
        printf("Number: ");
        ret = scanf("%ld", &credicard);
        if (ret != 0)
        {
            break;
        }
        scanf("%*s");
    }
    digits = getdigitss(credicard);
    credicard_str = malloc(digits + 1);

    sprintf(credicard_str, "%ld", credicard);

    for (ii = digits - 1, ret = 0, is_multiply = 0; ii > -1; ii--)
    {
        int helper = 0;
        if (is_multiply)
        {
            helper = 2 * ((int)credicard_str[ii] - 48);
            if (helper >= 10)
            {
                ret = ret + (helper % 10) + 1;
            }
            else
            {
                ret = ret + helper;
            }
            is_multiply = 0;
        }
        else
        {
            ret = ret + ((int)credicard_str[ii] - 48);
            is_multiply = 1;
        }
    }
    if ((ret % 10) != 0)
    {
        type = invalid;
    }

    getType(credicard_str, &type, digits);
    printfType(type);
    free(credicard_str);
}

void printfType(int type)
{
    switch (type)
    {
        case amex:
            printf("AMEX\n");
            break;
        case visa:
            printf("VISA\n");
            break;
        case mastercard:
            printf("MASTERCARD\n");
            break;
        case invalid:
            printf("INVALID\n");
            break;
    }
}

void getType(char *credicard_str, int *type, int digits)
{
    if (*type != invalid)
    {
        if (credicard_str[0] == '4')
        {
            if (digits == 13 || digits == 16)
            {
                *type = visa;
            }
            else
            {
                *type = invalid;
            }
        }
        else if ((credicard_str[0] == '3') &&
                 ((credicard_str[1] == '4') ||
                  (credicard_str[1] == '7')))
        {
            if (digits == 15)
            {
                *type = amex;
            }
            else
            {
                *type = invalid;
            }
        }
        else if ((credicard_str[0] == '5') && ((credicard_str[1] == '1') ||
                                               (credicard_str[1] == '2') || (credicard_str[1] == '3') ||
                                               (credicard_str[1] == '4') || (credicard_str[1] == '5')))
        {
            if (digits == 16)
            {
                *type = mastercard;
            }
            else
            {
                *type = invalid;
            }
        }
        else
        {
            *type = invalid;
        }
    }
}

int getdigitss(long count_numer)
{
    int count = 0;

    while (count_numer != 0)
    {
        count_numer /= 10;
        ++count;
    }
    return count;
}