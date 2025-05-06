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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


unsigned int wordCount = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashValue = hash(word);
    node* cursor = table[hashValue];
    while(cursor != NULL)
    {

        if(strcasecmp(cursor->word, word) == 0)
        {
           return true;
        }
        else
        {
            cursor = cursor->next;
        }

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        printf("file couldn't be openend\n");
        return false;
    }
    char buffer[LENGTH + 1];
   while (fscanf(dict, "%s", buffer) != EOF)
   {
    node* new_word = malloc(sizeof(node));
    int hashValue = hash(buffer);
    strcpy(new_word->word, buffer);
    new_word->next = table[hashValue];
    table[hashValue] = new_word;

    wordCount++;
   }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i= 0; i < N; i++)
    {
        node* cursor = table[i];
        while(cursor!= NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }

   return true;
}
