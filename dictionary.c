// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/time.h>

#include "dictionary.h"
#include "linked_list.h"

void print_hash_info(node* h_table[]);

/* node* hash_table[TABLE_SIZE]; */

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    /* if(!word) // just to shut the compiler up. Delete later */
    /* { */
    /*     return true; */
    /* } */
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    struct timeval tv1, tv4;
    gettimeofday(&tv1, NULL); //start the global timer


    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
      printf("Could not open %s.\n", dictionary);
      return false;
    }

    unsigned long word_count = 0;
    char raw_word[LENGTH + 1];
    unsigned long key = 0;
    unsigned long index = 0;

    node* hash_table[TABLE_SIZE];
    /* char* hash_table = malloc(sizeof(node *) * TABLE_SIZE); */

    for(int i=0; i<TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    while(fgets(raw_word, LENGTH + 1, dic))
    {
        raw_word[strcspn(raw_word, "\n")] = 0; // Strip the newline off the word
        key = hash(raw_word);
        index = get_index(key);
        /* printf("Hashed: %sKey: %lu\n", raw_word, key); */
        hash_table[index] = append(hash_table[index], key, raw_word);
        word_count++;
    }

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
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /* free(hash_table); */
    return false;
}

unsigned long get_index(unsigned long key)
{
    return (key % 65535);
}

void print_hash_info(node* h_table[])
{
 	  unsigned long none = 0;
    unsigned long used = 0;
    unsigned long lots = 0;
		unsigned long total = 0;
    unsigned int threshold = 7;
    unsigned int node_count[100] = {0};
    for(int i=0; i<TABLE_SIZE; i++)
    {
        unsigned int nodes = count_nodes(h_table[i]);
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
