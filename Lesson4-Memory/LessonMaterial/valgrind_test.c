#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr = malloc(12);
    arr[1] = 1;
    arr[2] = 3;
    arr[3] = 3; //valgrind will show that an error has been caught here

    free(arr);

    return 0;
}