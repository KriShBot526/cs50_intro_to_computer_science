#include <cs50.h>
#include <stdio.h>

bool check_validity(long long card_number);
int find_length(long long n);
bool checksum(long long cn);
void print_credit_card_brand(long long cn);

int main(void)
{
    long long card_number;

    //Taking credit card number from the user
    do
    {
        card_number = get_long_long("Number: ");
    }
    while (card_number <= 0);

    //Checking the validity of the card
    if (check_validity(card_number))
    {
        print_credit_card_brand(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_validity(long long card_number)
{
    int len = find_length(card_number);
    return (len == 13 || len == 15 || len == 16) && checksum(card_number);
}

int find_length(long long n)
{
    int len;
    for (len = 0; n != 0; n /= 10) //Calculating the length
    {
        len++;
    }

    return len;
}

// Applying checksum algorithm
bool checksum(long long cn)
{
    int sum = 0;
    for (int i = 0; cn != 0; i++)
    {
        if (i % 2 == 0) //Taking every 2nd digit and adding it
        {
            sum += cn % 10;
        }
        else //Taking every 2nd digit and adding it after doubling it
        {
            int digit = 2 * (cn % 10);
            sum += digit / 10 + digit % 10; //If we get 18 then the answer is 1+8 = 9
        }
        cn /= 10;
    }
    return (sum % 10) == 0;
}

void print_credit_card_brand(long long cn)
{
    //Checking the brand of cards
    if ((cn >= 34e13 && cn < 35e13) || (cn >= 37e13 && cn < 38e13))
    {
        printf("AMEX\n");
    }
    else if (cn >= 51e14 && cn < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((cn >= 4e12 && cn < 5e12) || (cn >= 4e15 && cn < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}