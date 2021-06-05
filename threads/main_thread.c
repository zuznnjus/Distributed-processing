#include "../main.h"
#include "../model/data.h"
#include "main_thread.h"
#include "../logic/state_reaction.h"

void mainLoop()
{
    int fightersOrMarines = 0;

    while (TRUE) 
    {
        switch (currentState)
        {
        case Mission:
            fightersOrMarines = missionStateReaction();
            break;

        case WaitWorkshop:
            waitWorkshopStateReaction(fightersOrMarines);
            break;

        case WaitHospital:
            waitHospitalStateReaction(fightersOrMarines);
            break;

        case WaitPubOne:
            waitPubOneStateReaction();
            break;

        case WaitPubTwo:
            waitPubTwoStateReaction();
            break; 

        case InWorkshop:
            inWorkshopStateReaction(fightersOrMarines);
            break;

        case InHospital:
            inHospitalStateReaction(fightersOrMarines);
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
