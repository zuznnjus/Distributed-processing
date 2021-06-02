#include "../main.h"
#include "../model/data.h"
#include "section.h"
#include "message_reaction.h"

void reqWorkshopReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    packet_t *pkt =  malloc(sizeof(packet_t));

    switch (currentState)
    {
    case WaitWorkshop:
        // TODO
        break;

    case InWorkshop:
        // TODO
        break;
    
    default:
        pkt->value = ACK_VALUE;
        sendPacket(pkt, packet.source, ACK_WORKSHOP);
        // dodaj do kolejki
        break;
    }
    
    free(pkt);
}

void reqHospitalReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    packet_t *pkt =  malloc(sizeof(packet_t));

    switch (currentState)
    {
    case WaitHospital:
        // TODO
        break;

    case InHospital:
        // TODO
        break;
    
    default:
        pkt->value = ACK_VALUE;
        sendPacket(pkt, packet.source, ACK_HOSPITAL);
        // dodaj do kolejki
        break;
    }

    free(pkt);
}

void reqPubOneReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    packet_t *pkt =  malloc(sizeof(packet_t));

    switch (currentState)
    {
    case WaitPubOne:
        // TODO
        break;

    case InPubOne:
        // TODO
        break;
    
    default:
        pkt->value = ACK_VALUE;
        sendPacket(pkt, packet.source, ACK_PUB_ONE);
        // dodaj do kolejki
        break;
    }

    free(pkt);
}

void reqPubTwoReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    packet_t *pkt =  malloc(sizeof(packet_t));

    switch (currentState)
    {
    case WaitPubTwo:
        // TODO
        break;

    case InPubTwo:
        // TODO
        break;
    
    default:
        pkt->value = ACK_VALUE;
        sendPacket(pkt, packet.source, ACK_PUB_TWO);
        // dodaj do kolejki
        break;
    }

    free(pkt);
}

void ackWorkshopReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    switch (currentState)
    {
    case WaitWorkshop:
        // TODO
        break;
    
    default:
        break;
    }
}

void ackHospitalReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    switch (currentState)
    {
    case WaitHospital:
        // TODO
        break;
    
    default:
        break;
    }
}

void ackPubOneReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    switch (currentState)
    {
    case WaitPubOne:
        // TODO
        break;
    
    default:
        break;
    }
}

void ackPubTwoReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    switch (currentState)
    {
    case WaitPubTwo:
        // TODO
        break;
    
    default:
        break;
    }
}

void releaseWorkshopReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    // TODO 
}

void releaseHospitalReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    // TODO 
}

void releasePubOneReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    // TODO 
}

void releasePubTwoReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    // TODO 
}