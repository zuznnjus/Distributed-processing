#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
 
typedef struct node {
    int rank;
    int priority;
    struct node* next;
 
} node_t;
 
node_t* newNode(int rank, int priority);
int peek(node_t** head);
void pop(node_t** head);
void push(node_t** head, int rank, int priority);
int isEmpty(node_t** head);

#endif