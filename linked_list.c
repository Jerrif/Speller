#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "linked_list.h"

unsigned long hash(char data[LENGTH + 1])
{
    int i = 0;
    unsigned long h = 1;
    /* for(int i=0; data[i]!=NULL || i<LENGTH + 1; i++) */
    while((data[i]!=10 && data[i]!=0) || i>LENGTH)
    {
        h *= data[i];
        /* printf("data[%i]: %i\nh: %d\n\n", i, data[i], h); */
        i++;
    }
    /* h = h % 65535; */
    return h;
}

int count_nodes(node* head)
{
    node* cursor = head;
    int i = 0;
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
    char buf[100];
    while(cursor != NULL)
    {
        /* printf("Value: %i, position in list: %i\n", cursor->data, i); */
        sprintf(buf, "Position in list: %i\tValue: %s", i, cursor->data);
        printf("%s\n", buf);
        cursor = cursor->next;
        i++;
    }
    printf("Done\n");
}

node* append(node* head, char data[LENGTH + 1])
{
    if(head == NULL)
    {
        node* new_node = create(head, data);
        head = new_node;
        return head;
    }
    node* cursor = head;
    while(cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    node* new_node = create(NULL, data);
    cursor->next = new_node;

    return head;
}

node* create(node* next, char data[LENGTH + 1])
{
    node* new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating new node\n");
        exit(0);
    }
    /* new_node->data = data; */
    strcpy(new_node->data, data);
    new_node->next = next;

    return new_node;
}
