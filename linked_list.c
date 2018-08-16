#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "linked_list.h"

// Hashing "algorithm" I came up with on the spot.
unsigned long hash(const char* data)
{
    int i = 0;
    unsigned long h = 1;
    while(data[i]!=0 || i>LENGTH)
    {
        /* h *= data[i]; */
        h = (h * data[i]) + i;
        i++;
    }
    return h;
}

bool find_value(node* head, unsigned long key, char* data)
{
    node* cursor = head;

    while(cursor != NULL)
    {
        if(cursor->key == key)
        {
            // Remember: strcmp returns 0 if they are equal
            if(!strcmp(cursor->data, data)) // So, if they ARE equal
            {
                return true;
            }
        }
        cursor = cursor->next;
    }

    return false;
}

bool free_list(node* head)
{
    node* cursor = head;
    node* temp = NULL;

    while(cursor != NULL)
    {
        temp = cursor->next;
        free(cursor);
        cursor = temp;
    }

    return true;
}

unsigned long count_nodes(node* head)
{
    node* cursor = head;
    unsigned long i = 0;
    while(cursor != NULL)
    {
        cursor = cursor->next;
        i++;
    }

    return i;
}

void print_list(node* head)
{
    node* cursor = head;
    int i = 1;
    char buf[150];
    while(cursor != NULL)
    {
        sprintf(buf, "Position in list: %i\tKey: %lu\tValue: %s", i, cursor->key, cursor->data);
        printf("%s\n", buf);
        cursor = cursor->next;
        i++;
    }
    printf("Done\n");
}

node* prepend(node* head, unsigned long key, char* data)
{
    node* new_node = create(head, key, data);
    head = new_node;
    return head;
}

node* append(node* head, unsigned long key, char* data)
{
    if(head == NULL)
    {
        node* new_node = create(head, key, data);
        head = new_node;
        return head;
    }
    node* cursor = head;
    while(cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    node* new_node = create(NULL, key, data);
    cursor->next = new_node;

    return head;
}

node* create(node* next, unsigned long key, char* data)
{
    node* new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating new node\n");
        exit(0);
    }
    /* new_node->data = data; */
    new_node->key = key;
    strcpy(new_node->data, data);
    new_node->next = next;

    return new_node;
}
