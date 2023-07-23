#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

float count_letters(string text);
float count_words(string text);
float count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float letters_count = count_letters(text);
    float words_count = count_words(text);
    float sentences_count = count_sentences(text);

    // Average letters per 100 words
    float L = (letters_count / words_count) * 100;

    //Average sentences per 100 words
    float S = (sentences_count / words_count) * 100;

    //Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //Prints the grade of the text
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


//Counts the number of letters
float count_letters(string text)
{
    float counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Check for alphabet
        if (isalpha(text[i]))
        {
            counter++;
        }
    }

    return counter;
}


// Counts the number of words
float count_words(string text)
{
    float counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            counter++;
        }
    }

    // Because there is spaces + 1 word in a sentence
    return counter + 1;
}


// Counts the number of sentences
float count_sentences(string text)
{
    float counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        // Check for punctuation marks
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }

    return counter;
}