#include "../main.h"
#include "state_reaction.h"
#include "section.h"
#include "../model/data.h"
#include "../threads/workshop_hospital_thread.h"
#include <pthread.h>

void missionStateReaction() 
{
    setMissionType();
    sleep(SEC_IN_STATE);

    if (currentMission == Flying) 
    {
        setBrokenFighters();
        debug("Skończyłem misję z myśliwcami");
        sleep(SEC_IN_STATE);
        debug("Zmieniam stan na WaitWorkshop");
        changeState(WaitWorkshop);
    } 
    else 
    {
        setInjuredMarines();
        debug("Skończyłem misję z bieganiem");
        sleep(SEC_IN_STATE);
        debug("Zmieniam stan na WaitHospital");
        changeState(WaitHospital);
    }
}

void waitWorkshopStateReaction()
{
    sendPacketToAll(brokenFighters, REQ_WORKSHOP);

    while (!canEnterWorkshop()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InWorkshop");
    changeState(InWorkshop);
}

void waitHospitalStateReaction()
{
    sendPacketToAll(injuredMarines, REQ_HOSPITAL);

    while (!canEnterHospital()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InHospital");
    changeState(InHospital);
}

void waitPubOneStateReaction()
{
    sendPacketToAll(teamMembers, REQ_PUB_ONE);

    while (!canEnterPubOne()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubOne");
    changeState(InPubOne);
}

void waitPubTwoStateReaction()
{
    sendPacketToAll(teamMembers, REQ_PUB_TWO);

    while (!canEnterPubTwo()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubTwo");
    changeState(InPubTwo);
}

void inWorkshopStateReaction()
{
    pthread_t workshopThread;
    pthread_create(&workshopThread, NULL, startWorkshopThread, NULL);

    sleep(SEC_IN_STATE);
    setPubNumber();

    if (pubNumber == PubOne) {
        debug("Zmieniam stan na WaitPubOne");
        changeState(WaitPubOne);
    }
    else
    {
        debug("Zmieniam stan na WaitPubTwo");
        changeState(WaitPubTwo);
    }
}

void inHospitalStateReaction()
{
    pthread_t hospitalThread;
    pthread_create(&hospitalThread, NULL, startHospitalThread, NULL);

    sleep(SEC_IN_STATE);
    setPubNumber();

    if (pubNumber == PubOne) {
        debug("Zmieniam stan na WaitPubOne");
        changeState(WaitPubOne);
    }
    else
    {
        debug("Zmieniam stan na WaitPubTwo");
        changeState(WaitPubTwo);
    }
}

void inPubOneStateReaction()
{
    int secInPub = rand() % 5;
    sleep(secInPub);

    int runningFighters = 0, capableMarines = 0;

    do {
        sleep(SEC_IN_STATE);
        runningFighters = teamMembers - brokenFighters;
        capableMarines = teamMembers - injuredMarines;
    } while (runningFighters == 0 || capableMarines == 0);

    sendPacketToAll(teamMembers, RELEASE_PUB_ONE);

    debug("Zmieniam stan na Mission");
    changeState(Mission);
}

void inPubTwoStateReaction()
{
    int secInPub = rand() % 5;
    sleep(secInPub);

    int runningFighters = 0, capableMarines = 0;

    do {
        sleep(SEC_IN_STATE);
        runningFighters = teamMembers - brokenFighters;
        capableMarines = teamMembers - injuredMarines;
    } while (runningFighters == 0 || capableMarines == 0);

    sendPacketToAll(teamMembers, RELEASE_PUB_TWO);

    debug("Zmieniam stan na Mission");
    changeState(Mission);
}
