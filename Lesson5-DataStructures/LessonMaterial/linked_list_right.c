#include <stdio.h>
#include <stdlib.h>

typedef struct DigitList
{
    int digit;
    struct DigitList* next_digit;
} digit_list;

//
// The right way(kinda)
//
int main()
{
    // Create a pointer to a linked list and set it to null
    digit_list* list = NULL;

    // Create the first object, validate it
    digit_list* foo = malloc(sizeof(digit_list));
    if (foo == NULL)
        return 1;

    // Set the first digit
    foo->digit = 1;
    foo->next_digit = NULL;

    // Linked list now points to the first object
    list = foo;

    // Create another object on the same variable(this doesnt free the memory)
    foo = malloc(sizeof(digit_list));
    if (foo == NULL)
    {
        free(foo);
        return 1;
    }

    // Set the digit
    foo->digit = 2;
    foo->next_digit = NULL;

    // List's next digit now points to the second object
    list->next_digit = foo;

    // create one more object
    foo = malloc(sizeof(digit_list));
    if (foo == NULL)
    {
        free(list->next_digit);
        free(list);
        return 1;
    }

    // Set the digit
    foo->digit = 3;
    foo->next_digit = NULL;

    // set the second object to point to the third one
    list->next_digit->next_digit = foo;

    // until the next digit ptr is null, keep on getting the next digit pointer
    for (digit_list* i = list; i != NULL; i = i->next_digit)
        // And print out the digit
        printf("%i\n", i->digit);
    

    // Free mem
    // free(list->next_digit->next_digit);
    // free(list->next_digit);
    // free(list);

    // If the current pointer in the variable list is not null, do the loop until it is
    while (list != NULL)
    {
        // make a copy of the next element in the list
        digit_list* tmp = list->next_digit;
        // deallocate the current list
        free(list);
        // list is now pointing to the next list
        list = tmp;
    }

    return 0;
}