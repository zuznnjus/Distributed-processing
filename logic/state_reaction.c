#include "../main.h"
#include "state_reaction.h"

void missionStateReaction() 
{
    setMissionType();
    sleep(SEC_IN_STATE);

    packet_t *pkt =  malloc(sizeof(packet_t));
    int msgType = 0;

    if (currentMission == Flying) 
    {
        setBrokenFighters();
        pkt->value = brokenFighters;
        msgType = REQ_WORKSHOP;
        debug("Skończyłem misję z myśliwcami");
    } else 
    {
        setInjuredMarines();
        pkt->value = injuredMarines;
        msgType = REQ_HOSPITAL;
        debug("Skończyłem misję z bieganiem");
    }

    sleep(SEC_IN_STATE);
    sendPacketToAll(pkt, msgType);
    
    if (currentMission == Flying) 
    {
        changeState(WaitWorkshop);
        debug("Zmieniam stan na WaitWorkshop");
    } else 
    {
        changeState(WaitHospital);
        debug("Zmieniam stan na WaitHospital");
    }
}

void waitWorkshopStateReaction()
{

}

void waitHospitalStateReaction()
{

}

void waitPubOneStateReaction()
{

}

void waitPubTwoStateReaction()
{

}

void inWorkshopStateReaction()
{

}

void inHospitalStateReaction()
{

}

void inPubOneStateReaction()
{

}

void inPubTwoStateReaction()
{

}

void sendPacketToAll(packet_t *pkt, int msgType)
{
    for (int i = 0; i < size; ++i) 
    {
        sendPacket(pkt, i, msgType);
    }
}