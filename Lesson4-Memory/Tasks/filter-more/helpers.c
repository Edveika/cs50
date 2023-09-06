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
