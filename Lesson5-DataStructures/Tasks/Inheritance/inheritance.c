// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int has_parents(person* p);
char random_allele_from_parents(person* p0, person* p1);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person* new_person = malloc(sizeof(person));
    person* p_new_person = new_person;
    char allele[2];

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        p_new_person->parents[0] = parent0;
        p_new_person->parents[1] = parent1;

        // Generate a new allele from parents
        allele[rand() % 2] = p_new_person->parents[0]->alleles[rand() % 2];
        allele[rand() % 2] = p_new_person->parents[1]->alleles[rand() % 2];
        
        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        strcpy(p_new_person->alleles, allele);
    }
    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        p_new_person->parents[0] = NULL;
        p_new_person->parents[1] = NULL;

        allele[0] = random_allele();
        allele[1] = random_allele();

        // TODO: Randomly assign alleles
        strcpy(p_new_person->alleles, allele);
    }

    // TODO: Return newly created person
    return new_person;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (!p->parents[0])
        return;

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

int has_parents(person* p)
{
    if (p->parents[0] && p->parents[1])
        return true;
    
    return false;
}

char random_allele_from_parents(person* p0, person* p1)
{
    int allele_parent = rand() % 2;

    if (allele_parent == 0)
        return p0->alleles[rand() % 2];
    else
        return p1->alleles[rand() % 2];
}