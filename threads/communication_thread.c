#include "../main.h"
#include "../logic/message_reaction.h"
#include "../model/data.h"
#include "communication_thread.h"

void *startCommunicationThread(void *ptr)
{
    MPI_Status status;
    packet_t packet;
    
    while (TRUE) { // nieskończona pętla czy jakieś currentState != InFinish 
	    debug("czekam na recv");
        MPI_Recv(&packet, 1, MPI_PAKIET_T, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	    setMaxLamport(packet.ts);
        	
        switch (status.MPI_TAG) {
            case REQ_WORKSHOP: 
                    reqWorkshopReaction();
                    debug("Dostałem wiadomość REQ_WORKSHOP od %d (%d popsutych myśliwców)", packet.source, packet.value);
                    break;
            case REQ_HOSPITAL: 
                    reqHospitalReaction();
                    debug("Dostałem wiadomość REQ_HOSPTIAL od %d (%d rannych)", packet.source, packet.value);
                    break;
            case REQ_PUB_ONE:
                    reqPubOneReaction(); 
                    //debug("Dostałem wiadomość REQ_PUB_ONE od %d (%d członków zespołu)", packet.src, packet.data);
                    break;
            case REQ_PUB_TWO:
                    reqPubTwoReaction(); 
                    //debug("Dostałem wiadomość REQ_PUB_TWO od %d (%d członków zespołu)", packet.src, packet.data);
                    break;
            case ACK_WORKSHOP: 
                    ackWorkshopReaction();
                    break;
            case ACK_HOSPITAL: 
                    ackHospitalReaction();
                    break;
            case ACK_PUB_ONE: 
                    ackPubOneReaction();
                    break;
            case ACK_PUB_TWO: 
                    ackPubTwoReaction();
                    break;
            case RELEASE_WORKSHOP: 
                    releaseWorkshopReaction();
                    break;
            case RELEASE_HOSPITAL: 
                    releaseHospitalReaction();
                    break;
            case RELEASE_PUB_ONE: 
                    releasePubOneReaction();
                    break;
            case RELEASE_PUB_TWO: 
                    releasePubTwoReaction();
                    break;
            default:
                    break;
        }
    }
}
