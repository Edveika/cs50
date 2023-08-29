#include <cs50.h>
#include <stdio.h>

void draw_stairs(int height);
void draw_stairs_recursion(int height);

int main()
{
    int height = get_int("height: ");

    draw_stairs_recursion(height);

    return 0;
}

void draw_stairs(int height)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < i + 1; ++j)
        {
            printf("#");
        }
        printf("\n");
    }
}

void draw_stairs_recursion(int height)
{
    if (height - 1 > 0)
        draw_stairs_recursion(height - 1);
    
    for (int i = 0; i < height; ++i)
        printf("#");

    printf("\n");
}