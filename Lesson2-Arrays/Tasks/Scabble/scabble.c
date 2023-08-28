#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// A=i_0,B=i_1,C=i_2...
const int ABC_SCORE[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

string capitalize_str(string str);
int get_score_from_str(string str);
string get_winner(string plr0_str, string plr1_str);

int main()
{
    string plr0_str = get_string("PLAYER 0: ");
    string plr1_str = get_string("PLAYER 1: ");

    string plr_winner = get_winner(plr0_str, plr1_str);

    if (plr_winner != "NULL")
        printf("%s\n", plr_winner);
    else
    {
        printf("Error encountered in get_winner fn\n");
        return 1;
    }

    return 0;
}

string capitalize_str(string str)
{
    string result = str;
    int str_len = strlen(result);

    for (int i = 0; i < str_len; ++i)
    {
        if (islower(result[i]))
            result[i] = toupper(result[i]);
    }

    return result;
}

int get_score_from_str(string str)
{
    int sum = 0;
    string cap_str = capitalize_str(str);
    int str_len = strlen(cap_str);

    for (int i = 0; i < str_len; ++i)
    {
        if (isupper((int)cap_str[i]))
        {
            int i_digit = (int)cap_str[i] - 65;
            sum += ABC_SCORE[i_digit];
        }
    }

    return sum;
}

string get_winner(string plr0_str, string plr1_str)
{
    int score_plr0 = get_score_from_str(plr0_str);
    int score_plr1 = get_score_from_str(plr1_str);

    if (score_plr0 > score_plr1)
        return "Player0 wins!";
    else if (score_plr0 < score_plr1)
        return "Player1 wins!";
    else
        return "Tie!";

    return "NULL";
}