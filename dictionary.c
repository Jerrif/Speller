// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "dictionary.h"
#include "linked_list.h"

void print_hash_info(node* h_table[]);

/* node* hash_table[TABLE_SIZE]; */
node** hash_table;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char lower_word[LENGTH + 1];
    int i = 0;

    do
    {
        lower_word[i] = (tolower(word[i]));
        i++;
    } while(word[i]!=0);

    lower_word[i] = 0;

    unsigned long key = 0, index = 0;
    key = hash(lower_word);
    index = get_index(key);

    return (find_value(hash_table[index], key, lower_word));

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
      printf("Could not open %s.\n", dictionary);
      return false;
    }

    // Start the hash function timer
    struct timeval tv1, tv4;
    gettimeofday(&tv1, NULL);

    unsigned long word_count = 0, key = 0, index = 0;
    char raw_word[LENGTH + 1];

    // Allocate global memory for the hash table
    /* node* hash_table[TABLE_SIZE]; */
    /* hash_table = malloc(sizeof(node) * TABLE_SIZE); */
    hash_table = calloc(TABLE_SIZE, sizeof(node));

    if(hash_table == NULL)
    {
        printf("Unable to allocate memory for dictionary table.\n");
        return false;
    }

    // Hash each word and add to hash table
    while(fgets(raw_word, LENGTH + 1, dic))
    {
        raw_word[strcspn(raw_word, "\n")] = 0; // Strip the newline off the word
        if(raw_word[0] != 0)                   // Don't count empty lines
        {
            key = hash(raw_word);
            index = get_index(key);
            hash_table[index] = prepend(hash_table[index], key, raw_word); // Prepend is much faster here than append (obviously)
            word_count++;
        }
    }

    // Get hash function timing
    gettimeofday(&tv4, NULL);
    double tt = (double) (tv4.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv4.tv_sec - tv1.tv_sec);

    print_hash_info(hash_table);
    printf("Word count: %lu\n", word_count);
    printf("\nHashing complete in %.4f seconds\n", tt);

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned long w_count = 0;

    for(int i=0; i<TABLE_SIZE; i++)
    {
        w_count += count_nodes(hash_table[i]);
    }

    return w_count;
}

// Unloads dictionary from memory, returning true if successful else false
// As far as I can tell, there's no way to test if memory has been freed "successfully"
// So this always returns true
bool unload(void)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        free_list(hash_table[i]);
    }
    free(hash_table);
    return true;
}

unsigned long get_index(unsigned long key)
{
    return (key % 65535);
}

void print_hash_info(node* h_table[]) // Note: equivalent to (node** h_table)
{
 	  unsigned long none = 0, used = 0, lots = 0, total = 0;
    unsigned int threshold = 7;
    unsigned int node_count[100] = {0};
    for(int i=0; i<TABLE_SIZE; i++)
    {
        unsigned long nodes = count_nodes(h_table[i]);
        if(nodes >= 1)
        {
            node_count[nodes]++;
            /* print_list(h_table[i]); */
            used++;
            if(nodes >= threshold)
            {
                lots++;
                /* printf("Nodes in Bucket[%u]:\t%u\n", i, nodes); */
                /* print_list(h_table[i]); */
                total += nodes;
            }
        }
        if(!nodes)
            none++;
        /* total += nodes; */
    }

    for(int i=0; i<100; i++)
    {
        if(node_count[i] > 0)
            printf("Buckets with %i nodes: %i\n", i, node_count[i]);
    }
    printf("\nUsed buckets: %lu\nBuckets > %d nodes: %lu\nUnused buckets: %lu\n", used, threshold, lots, none);
}
