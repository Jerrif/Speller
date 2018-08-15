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

node* create(node* next, unsigned long key, char data[LENGTH + 1]);
node* append(node* head, unsigned long key, char data[LENGTH + 1]);
void print_list(node* head);
int count_nodes(node* head);
unsigned long hash(char data[LENGTH + 1]);

#endif
