#include "../main.h"
#include "state_reaction.h"
#include "section.h"

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
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = brokenFighters;
    sleep(SEC_IN_STATE);
    sendPacketToAll(pkt, REQ_WORKSHOP);

    while (!canEnterWorkshop()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InWorkshop");
    changeState(InWorkshop);
}

void waitHospitalStateReaction()
{
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = injuredMarines;
    sleep(SEC_IN_STATE);
    sendPacketToAll(pkt, REQ_HOSPITAL);

    while (!canEnterHospital()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InHospital");
    changeState(InHospital);
}

void waitPubOneStateReaction()
{
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = teamMembers;
    sleep(SEC_IN_STATE);
    sendPacketToAll(pkt, REQ_PUB_ONE);

    while (!canEnterPubOne()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubOne");
    changeState(InPubOne);
}

void waitPubTwoStateReaction()
{
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = teamMembers;
    sleep(SEC_IN_STATE);
    sendPacketToAll(pkt, REQ_PUB_TWO);

    while (!canEnterPubTwo()) {
        sleep(SEC_IN_STATE);
    } 

    debug("Zmieniam stan na InPubTwo");
    changeState(InPubTwo);
}

void inWorkshopStateReaction()
{
    // TODO - nowy wątek w warsztacie
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
    // TODO - nowy wątek w szpitalu
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

    sleep(SEC_IN_STATE);
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = teamMembers;
    sendPacketToAll(pkt, RELEASE_PUB_ONE);

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

    sleep(SEC_IN_STATE);
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->value = teamMembers;
    sendPacketToAll(pkt, RELEASE_PUB_TWO);

    debug("Zmieniam stan na Mission");
    changeState(Mission);
}

void sendPacketToAll(packet_t *pkt, int msgType)
{
    for (int i = 0; i < size; ++i) 
    {
        sendPacket(pkt, i, msgType);
    }
}