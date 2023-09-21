// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// TODO: Choose number of buckets in hash table
const unsigned int N = 50;

// Hash table
node *table[N];

// Words in file intially
int sizew = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)]->next;
    while (cursor != NULL)
    {
        if (strcasecmp((cursor->word), word) == 0)
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
    // Hash function
    {
        unsigned int hashv = 1872;

        // Calculate the hash value
        for (int i = 0; word[i] != '\0' && i < 3; i++)
        {
            hashv += tolower(word[0]);
            hashv = hashv ^ (toupper(word[i]) - 'A');
        }

        return hashv % N;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *indict = fopen(dictionary, "r");
    if (indict == NULL)
    {
        printf("Couldnt Open Dictionary!\n");
        fclose(indict);
        return false;
    }

    // Allocates memory and Initializies Next Values in Hash Table to Null
    for (int i = 0; i < N; i++)
    {
        table[i] = (node *) malloc(sizeof(node));
        table[i]->next = NULL;
    }

    char buffer[46];
    fseek(indict, 0, SEEK_SET);

    while (fgets(buffer, 46, indict) != NULL)
    {
        if (strcasecmp(buffer, "\n") != 0)
        {
            node *term = malloc(sizeof(node));
            if (term == NULL)
            {
                printf("Malloc Failure!\n");
                return 1;
            }
            term->next = NULL;

            if (strlen(buffer) > 1)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(term->word, buffer);
            }

            else if (strlen(buffer) == 1)
            {
                term->word[0] = buffer[0];
                term->word[1] = '\0';
            }

            int hashv = hash(term->word);
            insert(term, hashv);
            sizew++;
        }
    }

    fclose(indict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded

unsigned int size(void)
{
    return sizew;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        memFree(table[i]);
    }
    return true;
}

// Inserts a new node into a linked list in the Hash Table
void insert(node *word, int hashv)
{
    node *new = word;
    new->next = table[hashv]->next;
    table[hashv]->next = new;
}

// Frees nodes recursively
void memFree(node *node)
{
    if (node->next != NULL)
    {
        memFree(node->next);
    }

    free(node);
}
