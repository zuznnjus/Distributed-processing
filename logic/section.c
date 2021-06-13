#include "section.h"

node_t *startNodeWorkshopQueue = NULL; //czy bez NULL mozna?
node_t *startNodeHospitalQueue = NULL; 
node_t *startNodePubOneQueue = NULL; 
node_t *startNodePubTwoQueue = NULL;  

pthread_mutex_t waitQueueWorkshopMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueueHospitalMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueuePubOneMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t waitQueuePubTwoMut = PTHREAD_MUTEX_INITIALIZER;

void updateWorkshopWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueWorkshopMut);
    debug("Wait_Queue_Workshop");
    printWaitQueue(&startNodeWorkshopQueue);
    updateParticularNode(&startNodeWorkshopQueue, pkt.source, pkt.value);
    pthread_mutex_unlock(&waitQueueWorkshopMut);
}

void updateHospitalWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueHospitalMut);
    debug("Wait_Queue_Hospital");
    printWaitQueue(&startNodeHospitalQueue);
    updateParticularNode(&startNodeHospitalQueue, pkt.source, pkt.value);
    pthread_mutex_unlock(&waitQueueHospitalMut);
}

void updatePubOneWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    debug("Wait_Queue_Pub_One");
    printWaitQueue(&startNodePubOneQueue);
    updateParticularNode(&startNodePubOneQueue, pkt.source, pkt.value);
    pthread_mutex_unlock(&waitQueuePubOneMut);
}

void updatePubTwoWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
    debug("Wait_Queue_Pub_Two");
    printWaitQueue(&startNodePubTwoQueue);
    updateParticularNode(&startNodePubTwoQueue, pkt.source, pkt.value);
    pthread_mutex_unlock(&waitQueuePubTwoMut);
}

int canEnterWorkshop() 
{
    pthread_mutex_lock(&waitQueueWorkshopMut);
    int reqSumWorkshop = sumValuesWithHigherPriority(&startNodeWorkshopQueue, rank);

    if (reqSumWorkshop <= W) 
    {
        int myTs = getParticularPriority(&startNodeWorkshopQueue, rank);
        checkRanksInWaitQueue(&startNodeWorkshopQueue, isInWorkshopQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInWorkshopQueue[i] && lastMessagePriorities[i] < myTs) 
            {
                pthread_mutex_unlock(&waitQueueWorkshopMut);
                return FALSE;
            }
        }
    }

	pthread_mutex_unlock(&waitQueueWorkshopMut);
    return TRUE;
}

int canEnterHospital()
{
    pthread_mutex_lock(&waitQueueHospitalMut);
    int reqSumHospital = sumValuesWithHigherPriority(&startNodeHospitalQueue, rank);

    if (reqSumHospital <= SZ) 
    {
        int myPriority = getParticularPriority(&startNodeHospitalQueue, rank);
        checkRanksInWaitQueue(&startNodeHospitalQueue, isInHospitalQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInHospitalQueue[i] && lastMessagePriorities[i] < myPriority) 
            {
                pthread_mutex_unlock(&waitQueueHospitalMut);
                return FALSE;
            }
        }
    }

	pthread_mutex_unlock(&waitQueueHospitalMut);
    return TRUE;
}

int canEnterPubOne()
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    int reqSumPubOne = sumValuesWithHigherPriority(&startNodePubOneQueue, rank);

    if (reqSumPubOne <= K) 
    {
        int myPriority = getParticularPriority(&startNodePubOneQueue, rank);
        checkRanksInWaitQueue(&startNodePubOneQueue, isInWorkshopQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInPubOneQueue[i] && lastMessagePriorities[i] < myPriority) 
            {
                pthread_mutex_unlock(&waitQueuePubOneMut);
                return FALSE;
            }
        }
    }

	pthread_mutex_unlock(&waitQueuePubOneMut);
    return TRUE;
}

int canEnterPubTwo()
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
    int reqSumPubTwo = sumValuesWithHigherPriority(&startNodePubTwoQueue, rank);

    if (reqSumPubTwo <= K) 
    {
        int myPriority = getParticularPriority(&startNodePubTwoQueue, rank);
        checkRanksInWaitQueue(&startNodePubTwoQueue, isInPubTwoQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInPubTwoQueue[i] && lastMessagePriorities[i] < myPriority) 
            {
                pthread_mutex_unlock(&waitQueuePubTwoMut);
                return FALSE;
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