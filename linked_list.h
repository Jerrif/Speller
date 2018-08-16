#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    struct node *next;
    unsigned long key;
    char data[LENGTH + 1];
} node;

node* create(node* next, unsigned long key, char* data);
node* append(node* head, unsigned long key, char* data);
void print_list(node* head);
unsigned long count_nodes(node* head);
unsigned long hash(const char* data);
/* unsigned long hash(char data[LENGTH + 1]); */
bool free_list(node* head);
bool find_value(node* head, unsigned long key, char* data);
node* prepend(node* head, unsigned long key, char* data);

#endif
