#include "../main.h"
#include "main_thread.h"
#include "../logic/state_reaction.h"

void mainLoop()
{
    srandom(rank);
    while (TRUE) 
    {
        switch (currentState)
        {
        case Mission:
            missionStateReaction();
            break;

        case WaitWorkshop:
            waitWorkshopStateReaction();
            break;

        case WaitHospital:
            waitHospitalStateReaction();
            break;

        case WaitPubOne:
            waitPubOneStateReaction();
            break;

        case WaitPubTwo:
            waitPubTwoStateReaction();
            break; 

        case InWorkshop:
            inWorkshopStateReaction();
            break;

        case InHospital:
            inHospitalStateReaction();
            break;

        case InPubOne:
            inPubOneStateReaction();
            break;

        case InPubTwo:
            inPubTwoStateReaction();
            break;                    
        
        default:
            break;
        }
    }
}
