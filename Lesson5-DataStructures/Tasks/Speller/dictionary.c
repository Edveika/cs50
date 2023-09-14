// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i_hash = hash(word);

    int word_len = strlen(word);
    char lwr_word[LENGTH + 1];
    for (int i = 0; i < word_len; ++i)
        lwr_word[i] = tolower(word[i]);

    lwr_word[word_len] = '\0';

    for (struct node* tmp = table[i_hash]; tmp != NULL; tmp = tmp->next)
        if (!strcmp(tmp->word, lwr_word))
            return true;

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE* input_file = fopen(dictionary, "r");
    if (input_file == NULL)
        return false;

    fseek(input_file, 0, SEEK_END);
    int file_size = ftell(input_file);
    rewind(input_file);

    int data_written = 0;

    while (data_written < file_size)
    {
        char c;
        int i = 0;
        char word[LENGTH];

        while (true)
        {
            c = fgetc(input_file);
            if (c == EOF)
                return true;
            else if (c == ' ' || c == '\n')
                break;

            word[i++] = c;
            ++data_written;
        }

        word[i] = '\0';

        if (strlen(word) >= 1)
        {
            node* new_node = malloc(sizeof(node));
            int i_hash = hash(word);
            strcpy(new_node->word, word);
            new_node->next = table[i_hash];
            table[i_hash] = new_node;
        }
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;

    for (int i = 0; i < N; ++i)
        for (struct node* tmp = table[i]; tmp != NULL; tmp = tmp->next)
            if (strlen(tmp->word) >= 1)
                word_count = word_count + 1;

    return word_count;
}

bool nodes_exist()
{
    for (int i = 0; i < N; ++i)
        for (struct node* tmp = table[i]; tmp != NULL; tmp = tmp->next)
            return true;

    return false;
}

void unload_node(node* node)
{
    if (node == NULL)
        return;

    unload_node(node->next);
    free(node);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if (!nodes_exist())
        return false;

    for (int i = 0; i < N; ++i)
        unload_node(table[i]);

    return true;
}
