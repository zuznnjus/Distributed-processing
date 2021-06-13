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
 
void push(node_t** head, int rank, int priority, int value) // im mniejszy priorytet, tym lepiej
{
    node_t* start = (*head);
    node_t* temp = newNode(rank, priority, value);
 
    if (start == NULL) 
    {
        (*head) = temp;
    }
    else if (start->priority > priority || (start->priority == priority && start->rank > rank)) 
    {
        temp->next = *head;
        (*head) = temp;
    }
    else
    {
        node_t *next;
        while ((next = start->next) != NULL && (next->priority < priority || (next->priority == priority && next->rank < rank))) 
        {
            start = next;
        }
 
        temp->next = start->next;
        start->next = temp;
    }
}

void updateParticularNode(node_t** head, int rank, int value)
{
    node_t *iterator = (*head);

    while (iterator != NULL) 
    {
        if (iterator->rank == rank) 
        {
            iterator->value -= value;
            if (iterator->value == 0) 
            {
                deleteParticularNode(head, rank);
            }
            break;
        }

        iterator = iterator->next;
    }
}

void deleteParticularNode(node_t** head, int rank)
{
    node_t *temp = (*head), *prev;
 
    if (temp != NULL && temp->rank == rank) {
        *head = temp->next; 
        free(temp); 
        return;
    }
 
    while (temp != NULL && temp->rank != rank) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return;
 
    prev->next = temp->next;
    free(temp);
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

int sumValuesWithHigherPriority(node_t** head, int rank)
{
    node_t *iterator = (*head);
    int valuesSum = 0;

    while (iterator->rank != rank && iterator != NULL) 
    {
        valuesSum += iterator->value;
        iterator = iterator->next;
    }

    if(iterator->rank == rank)
    {
        valuesSum += iterator->value;
    }

    return valuesSum;
}

int isEmpty(node_t** head)
{
    return (*head) == NULL;
}

void printWaitQueue(node_t** head, const char* name)
{
    node_t *iterator = (*head);
    char buffer[100];
    char *ptr = buffer; 

    ptr += sprintf(ptr, name);
    while (iterator != NULL) {
        ptr += sprintf(ptr, "[r:%d ts:%d] %d, ", iterator->rank, iterator->priority, iterator->value);
        iterator = iterator->next;
    }

    debug("%s", buffer);
}