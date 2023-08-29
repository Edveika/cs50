#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string names[] = { "David", "Edvinas", "Charlie", "Fred", "Jimmy", "Joe" };

    for (int i = 0; i < 6; ++i)
    {
        if (!strcmp(names[i], "Joe"))
        {
            printf("found\n");
            return 0;
        }
    }
    
    printf("not found\n");
    return 1;
}