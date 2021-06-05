#include "../main.h"
#include "state_reaction.h"
#include "section.h"
#include "../model/data.h"
#include "../threads/workshop_hospital_thread.h"
#include <pthread.h>

int missionStateReaction() 
{
    setMissionType();
    sleep(SEC_IN_STATE);

    int fightersOrMarines = 0;

    if (currentMission == Flying) 
    {
        fightersOrMarines = updateBrokenFighters();
        debug("Skończyłem misję z myśliwcami");
        sleep(SEC_IN_STATE);
        debug("Zmieniam stan na WaitWorkshop");
        changeState(WaitWorkshop);
    } 
    else 
    {
        fightersOrMarines = updateInjuredMarines();
        debug("Skończyłem misję z bieganiem");
        sleep(SEC_IN_STATE);
        debug("Zmieniam stan na WaitHospital");
        changeState(WaitHospital);
    }

    return fightersOrMarines;
}

void waitWorkshopStateReaction(int fighters)
{
    int myTs = sendPacketToAll(fighters, REQ_WORKSHOP);

    packet_t pkt;
    pkt.source = rank;
    pkt.ts = myTs;
    pkt.value = fighters;
    putInWorkshopWaitQueue(pkt);

    while (!canEnterWorkshop()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InWorkshop");
    changeState(InWorkshop);
}

void waitHospitalStateReaction(int marines)
{
    int myTs = sendPacketToAll(marines, REQ_HOSPITAL);

    packet_t pkt;
    pkt.source = rank;
    pkt.ts = myTs;
    pkt.value = marines;
    putInHospitalWaitQueue(pkt);

    while (!canEnterHospital()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InHospital");
    changeState(InHospital);
}

void waitPubOneStateReaction()
{
    int myTs = sendPacketToAll(teamMembers, REQ_PUB_ONE);

    packet_t pkt;
    pkt.source = rank;
    pkt.ts = myTs;
    pkt.value = teamMembers;
    putInPubOneWaitQueue(pkt);

    while (!canEnterPubOne()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubOne");
    changeState(InPubOne);
}

void waitPubTwoStateReaction()
{
    int myTs = sendPacketToAll(teamMembers, REQ_PUB_TWO);

    packet_t pkt;
    pkt.source = rank;
    pkt.ts = myTs;
    pkt.value = teamMembers;
    putInPubTwoWaitQueue(pkt);

    while (!canEnterPubTwo()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubTwo");
    changeState(InPubTwo);
}

void inWorkshopStateReaction(int fighters)
{
    pthread_t workshopThread;
    int *arg = malloc(sizeof(*arg));
    *arg = fighters;
    pthread_create(&workshopThread, NULL, startWorkshopThread, arg);

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

void inHospitalStateReaction(int marines)
{
    pthread_t hospitalThread;
    int *arg = malloc(sizeof(*arg));
    *arg = marines;
    pthread_create(&hospitalThread, NULL, startHospitalThread, arg);

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
