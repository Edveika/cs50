#include <stdio.h>
#include <cs50.h>

const int DIGIT_COUNT = 16;

long get_algorithm_sum(long card_digits);
bool is_card_valid(long card_digits);

int main()
{
    long credit_card_num = get_long("Credit card num: ");

    if (is_card_valid(credit_card_num))
        printf("Card is valid!\n");
    else
        printf("Card is not valid :(\n");

    return 0;
}

long get_algorithm_sum(long card_digits)
{
    long cur_digit = (card_digits) % 10;
    long digit_sum = 0;
    long iterations = 1;
    long step = 10;

    // 16 because iterations start from 1
    // iterations start from 1 so we can easily determine if its even or odd digit index
    while (iterations <= 16)
    {
        if (iterations % 2 == 0)
        {
            long tmp_sum = cur_digit * 2;
            if (tmp_sum >= 10)
            {
                digit_sum += tmp_sum % 10;
                digit_sum += (tmp_sum / 10) % 10;
            }
            else
            {
                digit_sum += tmp_sum;
            }
        }
        else
        {
            digit_sum += cur_digit;
        }
        
        cur_digit = (card_digits / step) % 10;

        step *= 10;
        ++iterations;
    }

    return digit_sum;
}

bool is_card_valid(long card_digits)
{
    long cur_digit = (card_digits) % 10;
    long iterations = 0;
    long step = 10;

    while (iterations <= 15)
    {   
        cur_digit = (card_digits / step) % 10;

        if (iterations == 14 && cur_digit != 4)
            return false;

        step *= 10;
        ++iterations;
    }

    if (get_algorithm_sum(card_digits) % 10 == 0)
        return true;

    return false;
}