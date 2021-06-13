#include "workshop_hospital_thread.h"
#include <pthread.h>
#include "../model/data.h"
#include "../main.h"
#include "../utils/priority_queue.h"
#include "../logic/section.h"

void *startWorkshopThread(void *arg)
{
    int fighters = *((int *) arg);
    free(arg);

    while (fighters > 0)
    {
        sleep(SEC_IN_WORKSHOP_HOSPITAL);
        fighters--;
        decrementBrokenFighters();

        pthread_mutex_lock(&waitQueueWorkshopMut);
        updateParticularNode(&startNodeWorkshopQueue, rank, FIXED_FIGHTERS);
        pthread_mutex_unlock(&waitQueueWorkshopMut);

        sendPacketToAll(FIXED_FIGHTERS, RELEASE_WORKSHOP);
    }
    
    pthread_exit(NULL);
}

void *startHospitalThread(void *arg)
{
    int marines = *((int *) arg);
    free(arg);

    while (marines > 0)
    {
        sleep(SEC_IN_WORKSHOP_HOSPITAL);
        marines--;
        decrementInjuredMarines();

        pthread_mutex_lock(&waitQueueHospitalMut);
        updateParticularNode(&startNodeHospitalQueue, rank, CAPABLE_MARINES);
        pthread_mutex_unlock(&waitQueueHospitalMut);

        sendPacketToAll(CAPABLE_MARINES, RELEASE_HOSPITAL);
    }
    
    pthread_exit(NULL);
}