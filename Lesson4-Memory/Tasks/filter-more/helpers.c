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
                        avgr_red *= image[i + k][l + j].rgbtRed;
                        avgr_green *= image[i + k][l + j].rgbtGreen;
                        avgr_blue *= image[i + k][l + j].rgbtBlue;
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
    const int G_X[3][3] = { { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } };
    const int G_Y[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };
    
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int sum_x_red = 0;
            int sum_x_green = 0;
            int sum_x_blue = 0;

            int sum_y_red = 0;
            int sum_y_green = 0;
            int sum_y_blue = 0;

            for (int y = 0; y < 3; ++y)
            {
                for (int x = 0; x < 3; ++x)
                {
                    if (i + y < height && j + x < width)
                    {
                        sum_x_red += G_X[x][y] * image[i][j].rgbtRed;
                        sum_x_green += G_X[x][y] * image[i][j].rgbtGreen;
                        sum_x_blue += G_X[x][y] * image[i][j].rgbtBlue;

                        sum_y_red += G_Y[x][y] * image[i][j].rgbtRed;
                        sum_y_green += G_Y[x][y] * image[i][j].rgbtGreen;
                        sum_y_blue += G_Y[x][y] * image[i][j].rgbtBlue;
                    }
                }
            }

            int g_red = sqrt((sum_x_red * sum_x_red) + (sum_y_red * sum_y_red));
            int g_green = sqrt((sum_x_green * sum_x_green) + (sum_y_green * sum_y_green));
            int g_blue = sqrt((sum_x_blue * sum_x_blue) + (sum_y_blue * sum_y_blue));

            if (g_red > 255)
                g_red = 255;
            else if (g_red < 0)
                g_red = 0;
            if (g_green > 255)
                g_green = 255;
            else if (g_green < 0)
                g_green = 0;
            if (g_blue > 255)
                g_blue = 255;
            else if (g_blue < 0)
                g_blue = 0;

            image[i][j].rgbtRed = g_red;
            image[i][j].rgbtGreen = g_green;
            image[i][j].rgbtBlue = g_blue;
        }
    }

    return;
}
