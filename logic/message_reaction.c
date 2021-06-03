#include "../model/data.h"
#include "../utils/priority_queue.h"
#include "section.h"
#include "message_reaction.h"

void reqWorkshopReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    int myTs = getParticularPriority(&startNodeWorkshopQueue, rank);

    switch (currentState)
    {
    case WaitWorkshop:
        putInWorkshopWaitQueue(packet);
        if (packet.ts < myTs) 
        {
            sendPacket(ACK_VALUE, packet.source, ACK_WORKSHOP);
        }
        break;

    case InWorkshop:
        if (packet.ts > myTs) 
        {
            putInWorkshopWaitQueue(packet);
        }
        break;
    
    default:
        putInWorkshopWaitQueue(packet);
        sendPacket(ACK_VALUE, packet.source, ACK_WORKSHOP);
        break;
    }
}

void reqHospitalReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    int myTs = getParticularPriority(&startNodeHospitalQueue, rank);

    switch (currentState)
    {
    case WaitHospital:
        putInHospitalWaitQueue(packet);
        if (packet.ts < myTs) 
        {
            sendPacket(ACK_VALUE, packet.source, ACK_HOSPITAL);
        }
        break;

    case InHospital:
        if (packet.ts > myTs) 
        {
            putInHospitalWaitQueue(packet);
        }
        break;
    
    default:
        putInHospitalWaitQueue(packet);
        sendPacket(ACK_VALUE, packet.source, ACK_HOSPITAL);
        break;
    }
}

void reqPubOneReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    int myTs = getParticularPriority(&startNodePubOneQueue, rank);

    switch (currentState)
    {
    case WaitPubOne:
        putInPubOneWaitQueue(packet);
        if (packet.ts < myTs) 
        {
            sendPacket(ACK_VALUE, packet.source, ACK_PUB_ONE);
        }
        break;

    case InPubOne:
        if (packet.ts > myTs) 
        {
            putInPubOneWaitQueue(packet);
        }
        break;
    
    default:
        putInPubOneWaitQueue(packet);
        sendPacket(ACK_VALUE, packet.source, ACK_PUB_ONE);
        break;
    }
}

void reqPubTwoReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    int myTs = getParticularPriority(&startNodePubTwoQueue, rank);

    switch (currentState)
    {
    case WaitPubTwo:
        putInPubTwoWaitQueue(packet);
        if (packet.ts < myTs) 
        {
            sendPacket(ACK_VALUE, packet.source, ACK_PUB_TWO);
        }
        break;

    case InPubTwo:
        if (packet.ts > myTs) 
        {
            putInPubTwoWaitQueue(packet);
        }
        break;
    
    default:
        putInPubTwoWaitQueue(packet);
        sendPacket(ACK_VALUE, packet.source, ACK_PUB_TWO);
        break;
    }
}

void ackWorkshopReaction(packet_t packet)
{
    switch (currentState)
    {
    case WaitWorkshop:
        updateLastMessagePriorities(packet.source, packet.ts);
        break;
    
    default:
        break;
    }
}

void ackHospitalReaction(packet_t packet)
{
    switch (currentState)
    {
    case WaitHospital:
        updateLastMessagePriorities(packet.source, packet.ts);
        break;
    
    default:
        break;
    }
}

void ackPubOneReaction(packet_t packet)
{
    switch (currentState)
    {
    case WaitPubOne:
        updateLastMessagePriorities(packet.source, packet.ts);
        break;
    
    default:
        break;
    }
}

void ackPubTwoReaction(packet_t packet)
{
    switch (currentState)
    {
    case WaitPubTwo:
        updateLastMessagePriorities(packet.source, packet.ts);
        break;
    
    default:
        break;
    }
}

void releaseWorkshopReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    updateWorkshopWaitQueueValues(packet);
}

void releaseHospitalReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    updateHospitalWaitQueueValues(packet);
}

void releasePubOneReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    updatePubOneWaitQueueValues(packet);
}

void releasePubTwoReaction(packet_t packet)
{
    updateLastMessagePriorities(packet.source, packet.ts);
    updatePubTwoWaitQueueValues(packet); 
}
