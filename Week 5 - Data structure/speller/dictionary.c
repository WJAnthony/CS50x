// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int number_of_words = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1125;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    int location = hash(word);

    // Search linked list at that location in hashtable
    node *tvr = table[location];
    while (tvr != NULL)
    {
        if (strcasecmp(word, tvr->word) == 0)
        {
            return true;
        }
        else
        {
            tvr = tvr->next;
        }
    }
    // if not found, return false
    return false;
}

// Hashes word by the total Ascii value of characters
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int ascii = (toupper(word[i]) - 65);
        if (ascii > 0 && ascii < 26)
        {
            sum += ascii;
        }
    }
    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictonary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // For each word, read it
    char buffer[LENGTH + 1];
    node *list = NULL;

    while (fscanf(source, "%s", buffer) != EOF)
    {
        // Create space for new hash node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }

        // Copy word into new node
        strcpy(n->word, buffer);
        n->next = NULL;

        // Hash word to obtain its has value
        int index_value = hash(n->word);

        // Insert new node into hash table
        // If hash table at index has nothing
        if (table[index_value] == NULL)
        {
            table[index_value] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index_value];
            table[index_value] = n;
        }
        number_of_words++;
    }

    // Close dictonary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 1125; i++)
    {
        node *head = table[i];
        while (head != NULL)
        {
            node *ptr = head->next;
            free(head);
            head = ptr;
        }
        free(head);
    }
    return true;
}
