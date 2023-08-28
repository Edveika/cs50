#include <cs50.h>
#include <stdio.h>

void draw_pyramid(int height);

int main()
{
    int height = 0;
    do
    {
        height = get_int("height: ");
    } while (height <= 1);

    draw_pyramid(height);

    return 0;
}

void draw_pyramid(int height)
{
    for (int i = 0; i < height; ++i)
    {
        int block_count = i + 1;

        // Fills in empty spaces on the left side of the pyramic
        int empty_count = height - block_count;
        while (empty_count != 0)
        {
            printf(" ");
            --empty_count;
        }

        // Draws cubes for the left side of the pyramid
        for (int j = 0; j < block_count; ++j)
        {
            printf("#");
        }

        // Empty space between 2 pyramids
        printf(" ");

        // Draws the right side of the pyramid
        for (int j = 0; j < block_count; ++j)
        {
            printf("#");
        }

        // Ends the line
        printf("\n");
    }
}