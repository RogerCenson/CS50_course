#include <stdio.h>

int main(void)
{
    int height;
    int ii, jj;
    //Keeps iterating until it gets a number between 1 and 8
    while (1)
    {
        printf("Height: ");
        scanf("%i", &height);
        if (height >= 1 && height <= 8)
        {
            break;
        }
    }
    // Numeber of lines
    for (ii = 0 ; ii < height; ii++)
    {
        // Maximum number of collouns
        for (jj = 0 ; jj < 2 * height + 2; jj++)
        {
            // Left part
            if (jj >= height - ii - 1 && jj < height)
            {
                printf("#");
            }
            // Right part
            else if (jj > height + 1 && jj <= height + ii + 2)
            {
                printf("#");
            }
            // Blanck parts
            else
            {
                printf(" ");
            }
            // Next line
            if (jj == height + ii + 2)
            {
                printf("\n");
                break;
            }
        }
    }

}
