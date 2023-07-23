#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");

    //Iterate the string chracter by character
    for (int i = 0; i < strlen(message); i++)
    {
        char c = message[i];

        // Convert the decimal into binary
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = c >> j & 1;
            print_bulb(bit);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
