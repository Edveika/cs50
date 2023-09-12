#include <stdio.h>
#include <math.h>

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
        for (int j = 0; j < width; ++j)
        {
            const int BLUR_STRENGHT = 12;
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
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            temp[i][j] = image[i][j];

    const int Gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    const int Gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;

            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if (i - 1 + x < 0 || i - 1 + x > height - 1 || j - 1 + y < 0 || j - 1 + y > width - 1)
                        continue;

                    redX = redX + (image[i - 1 + x][j - 1 + y].rgbtRed * Gx[x][y]);
                    greenX = greenX + (image[i - 1 + x][j - 1 + y].rgbtGreen * Gx[x][y]);
                    blueX = blueX + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gx[x][y]);

                    redY = redY + (image[i - 1 + x][j - 1 + y].rgbtRed * Gy[x][y]);
                    greenY = greenY + (image[i - 1 + x][j - 1 + y].rgbtGreen * Gy[x][y]);
                    blueY = blueY + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gy[x][y]);
                }
            }

            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            image[i][j] = temp[i][j];

    return;
}
