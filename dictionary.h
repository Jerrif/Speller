// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

/* #include "linked_list.h" */

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define TABLE_SIZE 256*256

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
unsigned long get_index(unsigned long key);

#endif // DICTIONARY_H
