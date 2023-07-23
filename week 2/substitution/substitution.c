#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void encipher(string plaintext, string key);
int test_arguments(int arguments, string key[]);

int main(int argc, string argv[])
{
    if (test_arguments(argc, argv))
    {
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    encipher(plaintext, argv[1]);
}

int test_arguments(int arguments, string key[])
{
    // Checking if the key is provided or not
    if (arguments != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key length is 26 or not
    else if (strlen(key[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(key[1]); i++)
    {
        // Check if the key have any characters other than alphabet
        if (!isalpha(key[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int j = 0; j < strlen(key[1]); j++)
        {
            // To check the duplicacy of letters present in key.
            if (toupper(key[1][i]) == toupper(key[1][j]) && i != j)
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }
    }
    return 0;
}

void encipher(string plaintext, string key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Stores a character in ci from plaintext
        char ci = plaintext[i];

        // Computes for uppercase characters
        if (isupper(ci))
        {
            int num = ci - 65;
            char c = toupper(key[num]);
            printf("%c", c);
        }
        // Computes for lower case characters
        else if (islower(ci))
        {
            int num = ci - 97;
            char c = tolower(key[num]);
            printf("%c", c);
        }
        // Computes for non alphabets
        else
        {
            printf("%c", ci);
        }
    }
    printf("\n");
}