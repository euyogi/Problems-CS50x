// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 25876; // Looks like a nice number, hash of 45 z's + 1 idk

// Hash table
node *table[N];

// Keep track of how many words there are in our dictionary
int words = 0;

void create_node(int bucket, char *word);
void free_bucket(int bucket);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // The idea is the same as in free_bucket(), but instead of calling free;
    // We compare the strings
    node *cursor = table[hash(word)];
    if (cursor != NULL)
    {
        while (cursor->next != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += (tolower(word[i]) - 'a') * (i + 1);
    }
    return hash % N;
}

// Create a node in a bucket
void create_node(int bucket, char *word)
{
    node *new = malloc(sizeof(node));
    strcpy(new->word, word);
    if (table[bucket] != NULL)
    {
        new->next = table[bucket];
    }
    else
    {
        new->next = NULL;
    }
    table[bucket] = new;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the dictionary file
    FILE *dicionario = fopen(dictionary, "r");
    if (dicionario == NULL)
    {
        fclose(dicionario);
        return false;
    }

    // Declares a buffer to a word and starts a counter
    char palavra[LENGTH + 1];
    int c = 0;

    // Create nodes and fill them with the words in our dictionary
    while (fscanf(dicionario, "%s", palavra) != EOF)
    {
        create_node(hash(palavra), palavra);
        words++;
    }

    fclose(dicionario);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (words > 0)
    {
        return words;
    }
    return 0;
}

// Delete all nodes in a bucket
void free_bucket(int bucket)
{
    // Define the cursor as the first node in the bucket
    node *cursor = table[bucket];

    // If there's no first node, we are done
    if (cursor != NULL)
    {
        // If there's more than 1 nodes, we'll free the atual node, and go to the next;
        // Repeating this proccess until there's no next
        node *temp = NULL;
        while (cursor->next != NULL)
        {
            temp = cursor->next;
            free(cursor);
            cursor = temp;
        }
        // This will free the last node, or, perhaps, the only one
        free(cursor);
    }
    return;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_bucket(i);
    }
    return true;
}
