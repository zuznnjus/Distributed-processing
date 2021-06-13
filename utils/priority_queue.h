#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
 
typedef struct node {
    int rank;
    int priority;
    int value;
    struct node* next;
} node_t;
 
node_t* newNode(int rank, int priority, int value);
int peek(node_t** head);
void pop(node_t** head);
void push(node_t** head, int rank, int priority, int value);

void updateParticularNode(node_t** head, int rank, int value);
void deleteParticularNode(node_t** head, int rank);
void checkRanksInWaitQueue(node_t** head, int* inWaitQueue); 
int getParticularPriority(node_t** head, int rank);
int sumValuesWithHigherPriority(node_t** head, int rank);
int isEmpty(node_t** head);
void printWaitQueue(node_t** head, const char* name);

#endif