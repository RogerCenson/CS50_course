#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int ii = 0, jj = 0;
    float helper = 0;
    for (ii = 0; ii < height; ii++)
    {
        for (jj = 0; jj < width; jj++)
        {
            helper = image[ii][jj].rgbtBlue + image[ii][jj].rgbtGreen + image[ii][jj].rgbtRed;
            helper = helper / 3;
            image[ii][jj].rgbtBlue = round(helper);
            image[ii][jj].rgbtGreen = round(helper);
            image[ii][jj].rgbtRed = round(helper);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int ii = 0, jj = 0;
    uint8_t rgbtBlue = 0, rgbtGreen = 0, rgbtRed = 0;
    for (ii = 0; ii < height; ii++)
    {
        for (jj = 0; jj < width / 2; jj++)
        {
            rgbtBlue = image[ii][jj].rgbtBlue;
            rgbtGreen = image[ii][jj].rgbtGreen;
            rgbtRed = image[ii][jj].rgbtRed;
            image[ii][jj].rgbtBlue = image[ii][width - jj - 1].rgbtBlue;
            image[ii][jj].rgbtGreen = image[ii][width - jj - 1].rgbtGreen;
            image[ii][jj].rgbtRed = image[ii][width - jj - 1].rgbtRed;
            image[ii][width - jj - 1].rgbtBlue = rgbtBlue;
            image[ii][width - jj - 1].rgbtGreen = rgbtGreen;
            image[ii][width - jj - 1].rgbtRed = rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int ii = 0, jj = 0, count = 0;
    int kk = 0, zz = 0;
    float rgbtBlue = 0, rgbtGreen = 0, rgbtRed = 0;
    RGBTRIPLE tmp_image[height][width];
    for (ii = 0; ii < height; ii++)
    {
        for (jj = 0; jj < width; jj++)
        {
            count = 0;
            rgbtBlue = 0;
            rgbtGreen = 0;
            rgbtRed = 0;
            for (kk = ii - 1; kk <= ii + 1; kk++)
            {
                for (zz = jj - 1; zz <= jj + 1; zz++)
                {
                    if (kk >= 0 && kk < height && zz >= 0 && zz < width)
                    {
                        count++;
                        rgbtBlue = rgbtBlue + image[kk][zz].rgbtBlue;
                        rgbtGreen = rgbtGreen + image[kk][zz].rgbtGreen;
                        rgbtRed = rgbtRed + image[kk][zz].rgbtRed;
                    }
                }
            }
            tmp_image[ii][jj].rgbtBlue = round(rgbtBlue / count);
            tmp_image[ii][jj].rgbtGreen = round(rgbtGreen / count);
            tmp_image[ii][jj].rgbtRed = round(rgbtRed / count);
        }
    }
    for (ii = 0; ii < height; ii++)
    {
        for (jj = 0; jj < width; jj++)
        {
            image[ii][jj].rgbtBlue = tmp_image[ii][jj].rgbtBlue;
            image[ii][jj].rgbtGreen = tmp_image[ii][jj].rgbtGreen;
            image[ii][jj].rgbtRed = tmp_image[ii][jj].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Generating temp image
    RGBTRIPLE tmp_image[height][width];

    // Creating the arrays for the Sobel Operator
    int Gx[3][3] =
    {
        { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 }
    };
    int Gy[3][3] =
    {
        { -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 }
    };

    // Declares counter for the positive and negative integers for the final operation
    float XrgbtBlue = 0, XrgbtGreen = 0, XrgbtRed = 0;
    float YrgbtBlue = 0, YrgbtGreen = 0, YrgbtRed = 0;

    // Going thru pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Clearing all counts
            XrgbtBlue = 0;
            XrgbtGreen = 0;
            XrgbtRed = 0;
            YrgbtBlue = 0;
            YrgbtGreen = 0;
            YrgbtRed = 0;

            // Checking the 3x3 dimension
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {

                    if ((i + y) < 0 || (i + y) == height || (j + x) < 0 || (j + x) == width)
                    {
                        continue;
                    }

                    // Adding 3x3 array to x/y_count
                    XrgbtRed += image[i + y][j + x].rgbtRed * Gx[y + 1][x + 1];
                    XrgbtGreen += image[i + y][j + x].rgbtGreen * Gx[y + 1][x + 1];
                    XrgbtBlue += image[i + y][j + x].rgbtBlue * Gx[y + 1][x + 1];

                    YrgbtRed += image[i + y][j + x].rgbtRed * Gy[y + 1][x + 1];
                    YrgbtGreen += image[i + y][j + x].rgbtGreen * Gy[y + 1][x + 1];
                    YrgbtBlue += image[i + y][j + x].rgbtBlue * Gy[y + 1][x + 1];

                }
            }

            // Sobel Operator on temp Image
            tmp_image[i][j].rgbtRed = round(fmin(255, sqrt((XrgbtRed * XrgbtRed) + (YrgbtRed * YrgbtRed))));
            tmp_image[i][j].rgbtGreen = round(fmin(255, sqrt((XrgbtGreen * XrgbtGreen) + (YrgbtGreen * YrgbtGreen))));
            tmp_image[i][j].rgbtBlue = round(fmin(255, sqrt((XrgbtBlue * XrgbtBlue) + (YrgbtBlue * YrgbtBlue))));


        }
    }

    // Copying the TempPicture to the original

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}