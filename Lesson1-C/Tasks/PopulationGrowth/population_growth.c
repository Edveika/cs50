#include <stdio.h>
#include <cs50.h>

int main()
{
    int llama_count_start = get_int("llama size: ");
    int llama_count_end = get_int("llama end size: ");
    int llama_count_cur = llama_count_start;
    int years = 0;

    do
    {
        int tmp_cur_count = llama_count_cur;

        llama_count_cur += tmp_cur_count / 3;
        llama_count_cur -= tmp_cur_count / 4;
        ++years;
    } while (llama_count_cur <= llama_count_end);

    printf("Years: %i\n", years);

    return 0;
}