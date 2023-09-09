#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct human
{
    char name[30];
} human;

typedef struct node
{
    human human;
    struct node* next;
} node;

int hash_function(char* name);

int main()
{
    int human_count = 0;
    scanf("%i", &human_count);

    if (human_count == 0)
        return 1;

    human humans[human_count];

    for (int i = 0; i < human_count; ++i)
        scanf("%30s", humans[i].name);

    // 26 because 1 bucket per letter
    node* hash_table[26];

    for (int i = 0; i < human_count; ++i)
    {
        int i_hash = hash_function(humans[i].name);
        node* node = hash_table[i_hash];

        while (node != NULL)
            node = hash_table[i_hash]->next;
        
        node = malloc(sizeof(node));
        strcpy(node->human.name, humans[i].name);
        node->next = NULL;
    }

    printf("%s\n", hash_table[0]->human.name);
    printf("%s\n", hash_table[0]->next->human.name);
    printf("%s\n", hash_table[0]->next->next->human.name);

    return 0;
}

int hash_function(char* name)
{
    // returns the index where this name should be stored in
    return tolower(name[0]) - 97;
}