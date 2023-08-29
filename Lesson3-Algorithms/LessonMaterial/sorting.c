#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string phone_number;
} person;

int main()
{
    person people[] = { { "David", "+36067890932" }, { "Kriks", "+36065487843" } };

    for (int i = 0; i < 2; ++i)
    {
        if (!strcmp(people[i].name, "Kriks"))
        {
            printf("%s\n", people[i].phone_number);
            return 0;
        }
    }

    printf("not found\n");
    return 1;
}