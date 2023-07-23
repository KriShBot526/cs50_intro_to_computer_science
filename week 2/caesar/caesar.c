#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void caesar_cipher(string plaintext, int key);

int main(int argc, string argv[])
{
    // Checks if any arguements is given
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // Checks for valid arguement if arguement is digit or not
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }

    // Converts string to integer
    int key = atoi(argv[1]);

    // Prompts for input message
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    caesar_cipher(plaintext, key);

    printf("\n");
}

void caesar_cipher(string plaintext, int key)
{
    for (int j = 0; j < strlen(plaintext); j++)
    {
        // Substitues the uppercase letter
        if (isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] + key - 65) % 26 + 65);
        }
        // Substitues the lowercase letter
        else if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] + key - 97) % 26 + 97);
        }
        // Prints any non alphabet as it is
        else
        {
            printf("%c", plaintext[j]);
        }
    }
}