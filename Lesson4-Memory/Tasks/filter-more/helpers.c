#include <stdio.h>

#include "helpers.h"

int max(int x, int y)
{
    return (x > y) ? x : y;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int biggest_value = max(image[i][j].rgbtRed, image[i][j].rgbtGreen);
            biggest_value = max(biggest_value, image[i][j].rgbtBlue);

            image[i][j].rgbtRed = biggest_value;
            image[i][j].rgbtGreen = biggest_value;
            image[i][j].rgbtBlue = biggest_value;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = j + 1; k < width; ++k)
            {
                RGBTRIPLE cpy = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = cpy;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 1; j < width; ++j)
        {
            const int BLUR_STRENGHT = 12;
            RGBTRIPLE average = { 0, 0, 0};
            int avgr_red = 0;
            int avgr_green = 0;
            int avgr_blue = 0;

            for (int k = 0; k < BLUR_STRENGHT; ++k)
            {
                for (int l = 0; l < BLUR_STRENGHT; ++l)
                {
                    if (i + k < height && l + j < width)
                    {
                        avgr_red += image[i + k][l + j].rgbtRed;
                        avgr_green += image[i + k][l + j].rgbtGreen;
                        avgr_blue += image[i + k][l + j].rgbtBlue;
                    }
                }
            }

            image[i][j].rgbtRed = avgr_red / (BLUR_STRENGHT * BLUR_STRENGHT);
            image[i][j].rgbtGreen = avgr_green / (BLUR_STRENGHT * BLUR_STRENGHT);
            image[i][j].rgbtBlue = avgr_blue / (BLUR_STRENGHT * BLUR_STRENGHT);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
        }
    }

    return;
}
