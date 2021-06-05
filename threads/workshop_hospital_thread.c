#include "workshop_hospital_thread.h"
#include <pthread.h>
#include "../model/data.h"
#include "../main.h"

void *startWorkshopThread(void *arg)
{
    int fighters = *((int *) arg);
    free(arg);

    while (fighters > 0)
    {
        sleep(SEC_IN_WORKSHOP_HOSPITAL);
        fighters--;
        decrementBrokenFighters();
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
        sendPacketToAll(CAPABLE_MARINES, RELEASE_HOSPITAL);
    }
    
    pthread_exit(NULL);
}