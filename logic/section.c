#include "section.h"

node_t *startNodeWorkshopQueue = NULL; 
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
    updateParticularNode(&startNodeWorkshopQueue, pkt.source, pkt.value);
    if (PRINT_QUEUES && currentState == WaitWorkshop) {
        printWaitQueue(&startNodeWorkshopQueue, "Wait_Queue_Workshop: ");
    }
    pthread_mutex_unlock(&waitQueueWorkshopMut);
}

void updateHospitalWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueHospitalMut);
    updateParticularNode(&startNodeHospitalQueue, pkt.source, pkt.value);
    if (PRINT_QUEUES && currentState == WaitHospital) {
        printWaitQueue(&startNodeHospitalQueue, "Wait_Queue_Hospital: ");
    }
    pthread_mutex_unlock(&waitQueueHospitalMut);
}

void updatePubOneWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    updateParticularNode(&startNodePubOneQueue, pkt.source, pkt.value);
    if (PRINT_QUEUES && currentState == WaitPubOne) {
        printWaitQueue(&startNodePubOneQueue, "Wait_Queue_Pub_One: ");
    }
    pthread_mutex_unlock(&waitQueuePubOneMut);
}

void updatePubTwoWaitQueueValues(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
    updateParticularNode(&startNodePubTwoQueue, pkt.source, pkt.value);
    if (PRINT_QUEUES && currentState == WaitPubTwo) {
        printWaitQueue(&startNodePubTwoQueue, "Wait_Queue_Pub_Two: ");
    }
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

        pthread_mutex_unlock(&waitQueueWorkshopMut);
        return TRUE;
    }

	pthread_mutex_unlock(&waitQueueWorkshopMut);
    return FALSE;
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

        pthread_mutex_unlock(&waitQueueHospitalMut);
        return TRUE;
    }

	pthread_mutex_unlock(&waitQueueHospitalMut);
    return FALSE;
}

int canEnterPubOne()
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    int reqSumPubOne = sumValuesWithHigherPriority(&startNodePubOneQueue, rank);

    if (reqSumPubOne <= K) 
    {
        int myPriority = getParticularPriority(&startNodePubOneQueue, rank);
        checkRanksInWaitQueue(&startNodePubOneQueue, isInPubOneQueue);

        for (int i = 0; i < size; i++) 
        {
            if (!isInPubOneQueue[i] && lastMessagePriorities[i] < myPriority) 
            {
                pthread_mutex_unlock(&waitQueuePubOneMut);
                return FALSE;
            }
        }

        pthread_mutex_unlock(&waitQueuePubOneMut);
        return TRUE;
    }

	pthread_mutex_unlock(&waitQueuePubOneMut);
    return FALSE;
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

        pthread_mutex_unlock(&waitQueuePubTwoMut);
        return TRUE;
    }

	pthread_mutex_unlock(&waitQueuePubTwoMut);
    return FALSE;
}

int canStartNewMission()
{
    int runningFighters = teamMembers - brokenFighters;
    int capableMarines = teamMembers - injuredMarines;

    return (runningFighters > 0 && capableMarines > 0);
}

void putInWorkshopWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueWorkshopMut);
    push(&startNodeWorkshopQueue, pkt.source, pkt.ts, pkt.value);
    if (PRINT_QUEUES && currentState == WaitWorkshop) {
        printWaitQueue(&startNodeWorkshopQueue, "Wait_Queue_Workshop: ");
    }
    pthread_mutex_unlock(&waitQueueWorkshopMut);
}

void putInHospitalWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueueHospitalMut);
    push(&startNodeHospitalQueue, pkt.source, pkt.ts, pkt.value);
    if (PRINT_QUEUES && currentState == WaitHospital) {
        printWaitQueue(&startNodeHospitalQueue, "Wait_Queue_Hospital: ");
    }
    pthread_mutex_unlock(&waitQueueHospitalMut);
}

void putInPubOneWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubOneMut);
    push(&startNodePubOneQueue, pkt.source, pkt.ts, pkt.value);
    if (PRINT_QUEUES && currentState == WaitPubOne) {
        printWaitQueue(&startNodePubOneQueue, "Wait_Queue_Pub_One: ");
    }
    pthread_mutex_unlock(&waitQueuePubOneMut);
}

void putInPubTwoWaitQueue(packet_t pkt)
{
    pthread_mutex_lock(&waitQueuePubTwoMut);
    push(&startNodePubTwoQueue, pkt.source, pkt.ts, pkt.value);
    if (PRINT_QUEUES && currentState == WaitPubTwo) {
        printWaitQueue(&startNodePubTwoQueue, "Wait_Queue_Pub_Two: ");
    }
    pthread_mutex_unlock(&waitQueuePubTwoMut);
}