#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool invalid_char(string str);
bool repeated_char(string str);
string encrypt_str(string str, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./app_name key\n");
        return 1;
    }
    string key = argv[1];
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 2;
    }
    if (invalid_char(key))
    {
        printf("Only A-Z, a-z supported\n");
        return 3;
    }
    if (repeated_char(key))
    {
        printf("All characters must be unique\n");
        return 4;
    }

    string input = get_string("plain text: ");
    string output = encrypt_str(input, key);

    printf("encrypted text: %s\n", output);

    return 0;
}

bool invalid_char(string str)
{
    int str_len = strlen(str);

    for (int i = 0; i < str_len; ++i)
    {
        if (!isupper(str[i]) && !islower(str[i]))
            return true;
    }

    return false;
}

bool repeated_char(string str)
{
    int str_len = strlen(str);

    for (int i = 0; i < str_len; ++i)
    {
        for (int j = i + 1; j < str_len; ++j)
        {
            // Makes both of the chars to lower case so we can check if they are not the same
            if (tolower(str[i]) == tolower(str[j]))
                return true;
        }
    }

    return false;
}

string encrypt_str(string str, string key)
{
    int str_len = strlen(str);
    int key_len = strlen(key);

    for (int i = 0; i < str_len; ++i)
    {
        if (isupper(str[i]))
        {
            int i_char = str[i] - 65;
            str[i] = toupper(key[i_char]);
        }
        else if (islower(str[i]))
        {
            int i_char = str[i] - 97;
            str[i] = tolower(key[i_char]);
        }
    }

    return str;
}