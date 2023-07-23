// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare variables
unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO: To check wether the word is present or not

    // Hash the word to obtain a hash value
    hash_value = hash(word);

    // Point cursor to the first node
    node *cursor = table[hash_value];

    // Go through the linked list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int n = (int) tolower(word[0]) - 97;
    return n;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO: Complete the load function

    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    // Returns NULL if file cannot be opened
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    char *dictword = malloc(LENGTH + 1);
    if (dictword == NULL)
    {
        return false;
    }

    // Read strings until we reach the end of the file (EOF)
    while (fscanf(file, "%s", dictword) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));

        // Returns false if malloc returns NULL
        if (n == NULL)
        {
            return false;
        }

        // copies the word in the chunk of memory allocated and then updates the words count
        strcpy(n->word, dictword);
        word_count++;

        // set next to point at beginning of list
        n->next = table[hash(dictword)];

        // set array to point at n which becomes new beginning of the list
        table[hash(dictword)] = n;
    }

    fclose(file);
    free(dictword);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO:

    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // creates two pointers to traverse the linked list and cancel its element without losing its address
    node *tmp;
    node *cursor;

    // repeats for every index in the table
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        cursor = table[i];
        tmp = cursor;

        // until the end of the list keeps freeing the memory allocated in load
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
