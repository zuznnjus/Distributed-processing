#include "priority_queue.h"
 
node_t* newNode(int rank, int priority)
{
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->rank = rank;
    temp->priority = priority;
    temp->next = NULL;
 
    return temp;
}
 
int peek(node_t** head)
{
    return (*head)->rank;
}
 
void pop(node_t** head)
{
    node_t* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
void push(node_t** head, int rank, int priority)
{
    node_t* start = (*head);
    node_t* temp = newNode(rank, priority);
 
    if ((*head)->priority > priority) {
        temp->next = *head;
        (*head) = temp;
    }
    else {
        while (start->next != NULL &&
            start->next->priority < priority) {
            start = start->next;
        }
 
        temp->next = start->next;
        start->next = temp;
    }
}

int isEmpty(node_t** head)
{
    return (*head) == NULL;
}