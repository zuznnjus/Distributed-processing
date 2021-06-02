#include "priority_queue.h"
#include "../main.h"
 
node_t* newNode(int rank, int priority, int value)
{
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->rank = rank;
    temp->priority = priority;
    temp->value = value;
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
 
void push(node_t** head, int rank, int priority, int value)
{
    node_t* start = (*head);
    node_t* temp = newNode(rank, priority, value);
 
    if (start == NULL) {
        (*head) = temp;
    }
    else if ((*head)->priority > priority) {
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

void updateParticularNode(node_t** head, int rank, int value)
{
    node_t *iterator = (*head);

    while (iterator != NULL) {
        if (iterator->rank == rank) {
            iterator->value += value;
            break;
        }

        iterator = iterator->next;
    }
}

void checkRanksInWaitQueue(node_t** head, int* inWaitQueue)
{
    node_t *iterator = (*head);

    for (int i = 0; i < size; i++) {
        inWaitQueue[i] = FALSE;
    }
    
    while (iterator != NULL) {
        inWaitQueue[iterator->rank] = TRUE;
        iterator = iterator->next;
    }
}

int getParticularPriority(node_t** head, int rank)
{
    node_t *iterator = (*head);

    while (iterator != NULL) {
        if (iterator->rank == rank) {
            return iterator->priority;
        }

        iterator = iterator->next;
    }

    return 0;
}

int isEmpty(node_t** head)
{
    return (*head) == NULL;
}