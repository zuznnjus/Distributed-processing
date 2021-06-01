#include "workshop_hospital_thread.h"
#include <pthread.h>
#include "../model/data.h"
#include "../main.h"

void *startWorkshopThread()
{
    int fighters = brokenFighters;

    while (fighters > 0)
    {
        sleep(1);
        fighters--;
        decrementBrokenFighters();
        sendPacketToAll(FIXED_FIGHTERS, RELEASE_WORKSHOP);
    }
    
    pthread_exit(NULL);
}

void *startHospitalThread()
{
    int marines = injuredMarines;

    while (marines > 0)
    {
        sleep(1);
        marines--;
        decrementInjuredMarines();
        sendPacketToAll(CAPABLE_MARINES, RELEASE_HOSPITAL);
    }
    
    pthread_exit(NULL);
}