#include <stdio.h>
#include <stdlib.h>

typedef struct DigitList
{
    int digit;
    struct DigitList* next_digit;
} digit_list;

//
// The wrong way
//
int main()
{
    digit_list* digit_0 = malloc(sizeof(digit_list));
    if (digit_0 == NULL)
        return 1;
    digit_0->digit = 1337;

    digit_list* digit_1 = malloc(sizeof(digit_list));
    if (digit_1 == NULL)
        return 1;
    digit_1->digit = 7331;

    digit_list* digit_2 = malloc(sizeof(digit_list));
    if (digit_2 == NULL)
        return 1;    // Free mem
    // free(list->next_digit->next_digit);
    // free(list->next_digit);
    // free(list);
    digit_0->next_digit = digit_1;
    digit_1->next_digit = digit_2;

    printf("%i\n", digit_0->next_digit->next_digit->digit);

    free(digit_0);
    free(digit_1);
    free(digit_2);

    return 0;
}