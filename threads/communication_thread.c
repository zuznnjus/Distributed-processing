#include "../main.h"
#include "../logic/message_reaction.h"
#include "../model/data.h"
#include "communication_thread.h"

void *startCommunicationThread(void *ptr)
{
    MPI_Status status;
    packet_t packet;
    
    while (TRUE) { 
        MPI_Recv(&packet, 1, MPI_PAKIET_T, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	    setMaxLamport(packet.ts);
        	
        pthread_mutex_lock(&sectionMut);    
        switch (status.MPI_TAG) {
            case REQ_WORKSHOP: 
                reqWorkshopReaction(packet);
                //debug("Dostałem wiadomość REQ_WORKSHOP od %d (%d popsutych myśliwców)", packet.source, packet.value);
                break;
            case REQ_HOSPITAL: 
                reqHospitalReaction(packet);
                //debug("Dostałem wiadomość REQ_HOSPTIAL od %d (%d rannych)", packet.source, packet.value);
                break;
            case REQ_PUB_ONE:
                reqPubOneReaction(packet); 
                //debug("Dostałem wiadomość REQ_PUB_ONE od %d (%d członków zespołu)", packet.source, packet.value);
                break;
            case REQ_PUB_TWO:
                reqPubTwoReaction(packet); 
                //debug("Dostałem wiadomość REQ_PUB_TWO od %d (%d członków zespołu)", packet.source, packet.value);
                break;
            case ACK_WORKSHOP: 
                ackWorkshopReaction(packet);
                //debug("Dostałem wiadomość ACK_WORKSHOP od %d", packet.source);
                break;
            case ACK_HOSPITAL: 
                ackHospitalReaction(packet);
                //debug("Dostałem wiadomość ACK_HOSPITAL od %d", packet.source);
                break;
            case ACK_PUB_ONE: 
                ackPubOneReaction(packet);
                //debug("Dostałem wiadomość ACK_PUB_ONE od %d", packet.source);
                break;
            case ACK_PUB_TWO: 
                ackPubTwoReaction(packet);
                //debug("Dostałem wiadomość ACK_PUB_TWO od %d", packet.source);
                break;
            case RELEASE_WORKSHOP: 
                releaseWorkshopReaction(packet);
                //debug("Dostałem wiadomość RELEASE_WORKSHOP od %d", packet.source);
                break;
            case RELEASE_HOSPITAL: 
                releaseHospitalReaction(packet);
                //debug("Dostałem wiadomość RELEASE_HOSPITAL od %d", packet.source);
                break;
            case RELEASE_PUB_ONE: 
                releasePubOneReaction(packet);
                //debug("Dostałem wiadomość RELEASE_PUB_ONE od %d", packet.source);
                break;
            case RELEASE_PUB_TWO: 
                releasePubTwoReaction(packet);
                //debug("Dostałem wiadomość RELEASE_PUB_TWO od %d", packet.source);
                break;
            default:
                break;
        }

        pthread_cond_signal(&sectionCond);
        pthread_mutex_unlock(&sectionMut);

    }
}
