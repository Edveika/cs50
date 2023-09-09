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

int valid_name(char* name);
int hash_function(char* name);
void insert_hash(node* hash_table[], char* name);
void print_hash(node* hash_table[]);
void free_node(node* node);
void free_hash(node* hash_table[]);

int main()
{
    int human_count = 0;
    scanf("%i", &human_count);

    if (human_count == 0)
        return 1;

    human humans[human_count];

    for (int i = 0; i < human_count; ++i)
    {
        scanf("%30s", humans[i].name);
        if (!valid_name(humans[i].name))
            return 2;
    }

    // 26 because 1 bucket per letter
    node* hash_table[26];

    // Set each element to NULL to avoid undefined behaviour
    for (int i = 0; i < 26; ++i)
        hash_table[i] = NULL;

    for (int i = 0; i < human_count; ++i)
        insert_hash(hash_table, humans[i].name);

    print_hash(hash_table);

    free_hash(hash_table);

    return 0;
}

int valid_name(char* name)
{
    int name_len = strlen(name);

    for (int i = 0; i < name_len; ++i)
        if (!islower(name[i]) && !isupper(name[i]))
            return 0;

    return 1;
}

int hash_function(char* name)
{
    // returns the index where this name should be stored in
    return tolower(name[0]) - 97;
}

void insert_hash(node* hash_table[], char* name) 
{
    // Gets the index of the abc array where names are stored via hash fn
    int i_hash = hash_function(name);

    // Creates a new node with the new node
    node* new_node = malloc(sizeof(node));
    strcpy(new_node->human.name, name);
    new_node->next = NULL;

    // Sets the next node ptr to the previos node
    new_node->next = hash_table[i_hash];

    // Sets the current hash_table node to be the node that was just created
    // Basically creates a new node and moves the old one to the right(next)
    hash_table[i_hash] = new_node;
}

void print_hash(node* hash_table[])
{
    for (int i = 0; i < 26; ++i)
    {
        if (hash_table[i])
        {   
            printf("Bucket: %c\n", i+97);

            for (node* tmp = hash_table[i]; tmp; tmp = tmp->next)
            {
                printf("%s\n", tmp->human.name);
            }
        }
    }
}

void free_node(node* node)
{
    if (!node)
        return;

    free_node(node->next);

    free(node);
}

void free_hash(node* hash_table[])
{
    for (int i = 0; i < 26; ++i)
        free_node(hash_table[i]);
}