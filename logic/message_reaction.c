//#include "../main.h"
//#include "../threads/main_thread.h"
#include "../model/data.h"
#include "message_reaction.h"

void reqWorkshopReaction()
{
    switch (currentState)
    {
    case WaitWorkshop:
        // TODO
        break;

    case InWorkshop:
        // TODO
        break;
    
    default:
        // TODO odsyłamy ACK
        break;
    }
}

void reqHospitalReaction()
{
    switch (currentState)
    {
    case WaitHospital:
        // TODO
        break;

    case InHospital:
        // TODO
        break;
    
    default:
        // TODO odsyłamy ACK
        break;
    }
}

void reqPubOneReaction()
{
    switch (currentState)
    {
    case WaitPubOne:
        // TODO
        break;

    case InPubOne:
        // TODO
        break;
    
    default:
        // TODO odsyłamy ACK
        break;
    }
}

void reqPubTwoReaction()
{
    switch (currentState)
    {
    case WaitPubTwo:
        // TODO
        break;

    case InPubTwo:
        // TODO
        break;
    
    default:
        // TODO odsyłamy ACK
        break;
    }
}

void ackWorkshopReaction()
{
    switch (currentState)
    {
    case WaitWorkshop:
        // TODO
        break;
    
    default:
        // TODO update last priorities
        break;
    }
}

void ackHospitalReaction()
{
    switch (currentState)
    {
    case WaitHospital:
        // TODO
        break;
    
    default:
        // TODO update last priorities
        break;
    }
}

void ackPubOneReaction()
{
    switch (currentState)
    {
    case WaitPubOne:
        // TODO
        break;
    
    default:
        // TODO update last priorities
        break;
    }
}

void ackPubTwoReaction()
{
    switch (currentState)
    {
    case WaitPubTwo:
        // TODO
        break;
    
    default:
        // TODO update last priorities
        break;
    }
}

void releaseWorkshopReaction()
{
    // TODO 
}

void releaseHospitalReaction()
{
    // TODO 
}

void releasePubOneReaction()
{
    // TODO 
}

void releasePubTwoReaction()
{
    // TODO 
}