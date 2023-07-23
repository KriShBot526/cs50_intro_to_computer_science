#include <stdio.h>
#include<cs50.h>

int main(void)
{
    //This line takes the name from the user
    string name = get_string("What's your name? ");

    //This line prints the greeting message with the name taken from the user
    printf("Hello, %s\n", name);
}