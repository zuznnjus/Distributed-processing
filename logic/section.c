#include "section.h"

int reqSumHospital, reqSumWorkshop, reqSumPubOne, reqSumPubTwo; 

node_t *startNodeWorkshopQueue = NULL; //czy bez NULL mozna?
node_t *startNodeHospitalQueue = NULL; 
node_t *startNodePubOneQueue = NULL; 
node_t *startNodePubTwoQueue = NULL;  

pthread_mutex_t waitQueueWorkshopMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueueHospitalMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueuePubOneMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueuePubTwoMut = PTHREAD_MUTEX_INITIALIZER;

void updateReqSumWorkshop(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueWorkshopMut);
    reqSumWorkshop += pkt.value;
    updateParticularNode(&startNodeWorkshopQueue, pkt.source, pkt.value); // TODO - usuwanie?
    if (startNodeWorkshopQueue->value == 0) 
    {
        pop(&startNodeWorkshopQueue);
    }
    pthread_mutex_unlock(&waitQueueWorkshopMut);
}

void updateReqSumHospital(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueHospitalMut);
    reqSumHospital += pkt.value;
    updateParticularNode(&startNodeHospitalQueue, pkt.source, pkt.value);
    if (startNodeWorkshopQueue->value == 0) 
    {
        pop(&startNodeHospitalQueue);
    }
    pthread_mutex_unlock(&waitQueueHospitalMut);
}

void updateReqSumPubOne(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    reqSumPubOne += pkt.value;
    updateParticularNode(&startNodePubOneQueue, pkt.source, pkt.value);
    if (startNodePubOneQueue->value == 0) 
    {
        pop(&startNodePubOneQueue);
    }
    pthread_mutex_unlock(&waitQueuePubOneMut);
}

void updateReqSumPubTwo(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
    reqSumPubTwo += pkt.value;
    updateParticularNode(&startNodePubTwoQueue, pkt.source, pkt.value);
    if (startNodePubTwoQueue->value == 0) 
    {
        pop(&startNodePubTwoQueue);
    }
    pthread_mutex_unlock(&waitQueuePubTwoMut);
}

int canEnterWorkshop() 
{
    pthread_mutex_lock(&waitQueueWorkshopMut);

    if (reqSumWorkshop <= W) 
    {
        int myPriority = getParticularPriority(&startNodeWorkshopQueue, rank);
        checkRanksInWaitQueue(&startNodeWorkshopQueue, isInWorkshopQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInWorkshopQueue[i]) 
            {
                if (lastMessagePriorities[i] < myPriority) 
                {
                    pthread_mutex_unlock(&waitQueueWorkshopMut);
                    return FALSE;
                }
            }
        }
    }

	pthread_mutex_unlock(&waitQueueWorkshopMut);
    return TRUE;
}

int canEnterHospital()
{
    pthread_mutex_lock(&waitQueueHospitalMut);

    if (reqSumHospital <= SZ) 
    {
        int myPriority = getParticularPriority(&startNodeHospitalQueue, rank);
        checkRanksInWaitQueue(&startNodeHospitalQueue, isInHospitalQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInHospitalQueue[i]) 
            {
                if (lastMessagePriorities[i] < myPriority) 
                {
                    pthread_mutex_unlock(&waitQueueHospitalMut);
                    return FALSE;
                }
            }
        }
    }

	pthread_mutex_unlock(&waitQueueHospitalMut);
    return TRUE;
}

int canEnterPubOne()
{
    pthread_mutex_lock(&waitQueuePubOneMut);

    if (reqSumPubOne <= K) 
    {
        int myPriority = getParticularPriority(&startNodePubOneQueue, rank);
        checkRanksInWaitQueue(&startNodePubOneQueue, isInWorkshopQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInPubOneQueue[i]) 
            {
                if (lastMessagePriorities[i] < myPriority) 
                {
                    pthread_mutex_unlock(&waitQueuePubOneMut);
                    return FALSE;
                }
            }
        }
    }

	pthread_mutex_unlock(&waitQueuePubOneMut);
    return TRUE;
}

int canEnterPubTwo()
{
    pthread_mutex_lock(&waitQueuePubTwoMut);

    if (reqSumPubTwo <= K) 
    {
        int myPriority = getParticularPriority(&startNodePubTwoQueue, rank);
        checkRanksInWaitQueue(&startNodePubTwoQueue, isInPubTwoQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInPubTwoQueue[i]) 
            {
                if (lastMessagePriorities[i] < myPriority) 
                {
                    pthread_mutex_unlock(&waitQueuePubTwoMut);
                    return FALSE;
                }
            }
        }
    }

	pthread_mutex_unlock(&waitQueuePubTwoMut);
    return TRUE;
}

void putInWorkshopWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueWorkshopMut);
	push(&startNodeWorkshopQueue, pkt.source, pkt.ts, pkt.value);
	pthread_mutex_unlock(&waitQueueWorkshopMut);
}

void putInHospitalWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueHospitalMut);
	push(&startNodeHospitalQueue, pkt.source, pkt.ts, pkt.value);
	pthread_mutex_unlock(&waitQueueHospitalMut);
}

void putInPubOneWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubOneMut);
	push(&startNodePubOneQueue, pkt.source, pkt.ts, pkt.value);
	pthread_mutex_unlock(&waitQueuePubOneMut);
}

void putInPubTwoWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
	push(&startNodePubTwoQueue, pkt.source, pkt.ts, pkt.value);
	pthread_mutex_unlock(&waitQueuePubTwoMut);
}