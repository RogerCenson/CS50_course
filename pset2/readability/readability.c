#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 1000

void printGrade(float grade);

int main(void)
{
    float grade = 0;
    int ii = 0;
    float nLetters = 0,  nWords = 1,  nSentences = 0;
    char text[MAX];
    printf("text: ");
    scanf("%[^\n]", text);

    while (text[ii] != '\0')
    {
        if (((int)text[ii] >= 65 && (int)text[ii] <= 90) ||
            ((int)text[ii] >= 97 && (int)text[ii] <= 122))
        {
            nLetters++;
        }
        else if (text[ii - 1] != ' ' && text[ii] == ' ' && text[ii + 1] != ' ')
        {
            nWords++;
        }
        else if (text[ii] == '.' || text[ii] == '!' || text[ii] == '?')
        {
            nSentences++;
        }
        ii++;
    }
    grade = 0.0588 * ((100 * nLetters) / nWords) - 0.296 * ((100 * nSentences) / nWords) - 15.8;
    // printf("%f letter(s)\n", nLetters);
    // printf("%f word(s)\n", nWords);
    // printf("%f sentence(s)\n", nSentences);
    printGrade(grade);

}

void printGrade(float grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)round(grade));
    }
}