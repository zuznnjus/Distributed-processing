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
        debug("Skończyłem misję z myśliwcami, zmieniam stan na WaitWorkshop");
        changeState(WaitWorkshop);
    } 
    else 
    {
        fightersOrMarines = updateInjuredMarines();
        debug("Skończyłem misję z bieganiem, zmieniam stan na WaitHospital");
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

    pthread_mutex_lock(&sectionMut);
    while (!canEnterWorkshop()) 
    {
        pthread_cond_wait(&sectionCond, &sectionMut);
    } 
    pthread_mutex_unlock(&sectionMut);

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

    pthread_mutex_lock(&sectionMut);
    while (!canEnterHospital()) 
    {
        pthread_cond_wait(&sectionCond, &sectionMut);
    } 
    pthread_mutex_unlock(&sectionMut);

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

    pthread_mutex_lock(&sectionMut);
    while (!canEnterPubOne()) 
    {
        pthread_cond_wait(&sectionCond, &sectionMut);
    } 
    pthread_mutex_unlock(&sectionMut);

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

    pthread_mutex_lock(&sectionMut);
    while (!canEnterPubTwo()) 
    {
        pthread_cond_wait(&sectionCond, &sectionMut);
    } 
    pthread_mutex_unlock(&sectionMut);

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

    pthread_mutex_lock(&fightersMarinesMut);
    while(!canStartNewMission)
    {
        pthread_cond_wait(&fightersMarinesCond, &fightersMarinesMut);
    }
    pthread_mutex_unlock(&fightersMarinesMut);

    sendPacketToAll(teamMembers, RELEASE_PUB_ONE);

    debug("Zmieniam stan na Mission");
    changeState(Mission);
}

void inPubTwoStateReaction()
{
    int secInPub = rand() % 5;
    sleep(secInPub);

    pthread_mutex_lock(&fightersMarinesMut);
    while(!canStartNewMission)
    {
        pthread_cond_wait(&fightersMarinesCond, &fightersMarinesMut);
    }
    pthread_mutex_unlock(&fightersMarinesMut);

    sendPacketToAll(teamMembers, RELEASE_PUB_TWO);

    debug("Zmieniam stan na Mission");
    changeState(Mission);
}
