// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/time.h>

#include "dictionary.h"
#include "linked_list.h"

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

    char raw_word[LENGTH + 1];
    unsigned long key = 0;
    unsigned long index = 0;

    node* hash_table[TABLE_SIZE];

    for(int i=0; i<TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    while(fgets(raw_word, LENGTH + 1, dic))
    {
        raw_word[strcspn(raw_word, "\n")] = 0;
        key = hash(raw_word);
        /* key = 10; */
        /* printf("Hashed: %sKey: %lu\n", raw_word, key); */
        hash_table[key] = append(hash_table[key], raw_word);
        /* printf("Word: %sHash: %lu\n", raw_word, key); */
        /* head = append(head, raw_word); */
    }

    gettimeofday(&tv4, NULL);
    double tt = (double) (tv4.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv4.tv_sec - tv1.tv_sec);

	  unsigned long none = 0;
    unsigned long used = 0;
    unsigned long lots = 0;
		unsigned long total = 0;
    unsigned int threshold = 10;
    for(int i=0; i<TABLE_SIZE; i++)
    {
        unsigned int nodes = count_nodes(hash_table[i]);
        if(nodes >= 1)
        {
            /* print_list(hash_table[i]); */
            used++;
            if(nodes >= threshold)
            {
                lots++;
                printf("Nodes in Bucket[%u]:\t%u\n", i, nodes);
                print_list(hash_table[i]);
            }
        }
        if(!nodes)
            none++;
        total += nodes;
    }
    printf("\nUsed nodes: %lu\nNodes > %d: %lu\nUnused nodes: %lu\nAverage node count: %f\n", used, threshold, lots, none, (double)total/(double)TABLE_SIZE);

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

    return false;
}
