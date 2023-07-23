#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //Use to take input from the user
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //Condition check the range of number should be between 1 to 8

    //Iterate through height
    for (int i = 1; i <= height; i++)
    {
        //Print spaces in decreasing order
        for (int j = i; j < height; j++)
        {
            printf(" ");
        }

        //Print bricks in increasing order
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        //print spaces between 2 pyramids
        printf("  ");

        //Print bricks for the 2nd pyramid
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}