#include "main.h"
#include "threads/communication_thread.h"
#include "threads/main_thread.h"

#include "time.h"
#include <pthread.h>

/* sem_init sem_destroy sem_post sem_wait */
//#include <semaphore.h>
/* flagi dla open */
//#include <fcntl.h>

int size, rank; 
MPI_Datatype MPI_PAKIET_T;
pthread_t communicationThread; 

int lamportClock;

void check_thread_support(int provided)
{
    switch (provided) {
        case MPI_THREAD_SINGLE: 
            printf("Brak wsparcia dla wątków, kończę\n");
            fprintf(stderr, "Brak wystarczającego wsparcia dla wątków - wychodzę!\n");
            MPI_Finalize();
            exit(-1);
            break;
        case MPI_THREAD_FUNNELED: 
            printf("tylko te wątki, ktore wykonaly mpi_init_thread mogą wykonać wołania do biblioteki mpi\n");
	        break;
        case MPI_THREAD_SERIALIZED: 
            printf("tylko jeden watek naraz może wykonać wołania do biblioteki MPI\n");
	        break;
        case MPI_THREAD_MULTIPLE: 
            printf("Pełne wsparcie dla wątków\n"); 
            break;
        default: 
            printf("Nikt nic nie wie\n");
    }
}

void initialize(int *argc, char ***argv)
{
    int provided;
    MPI_Init_thread(argc, argv, MPI_THREAD_MULTIPLE, &provided);
    check_thread_support(provided);

    const int nitems = 3; 
    int blocklengths[3] = {1, 1, 1};
    MPI_Datatype msgTypes[3] = {MPI_INT, MPI_INT, MPI_INT};

    MPI_Aint offsets[3]; 
    offsets[0] = offsetof(packet_t, ts);
    offsets[1] = offsetof(packet_t, source);
    offsets[2] = offsetof(packet_t, value);

    MPI_Type_create_struct(nitems, blocklengths, offsets, msgTypes, &MPI_PAKIET_T);
    MPI_Type_commit(&MPI_PAKIET_T);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srandom(rank);

    setTeamMembers();
    lastMessagePriorities = (int *) calloc(size, sizeof(int));
    isInWorkshopQueue = (int *) calloc(size, sizeof(int));
    isInHospitalQueue = (int *) calloc(size, sizeof(int));
    isInPubOneQueue = (int *) calloc(size, sizeof(int));
    isInPubTwoQueue = (int *) calloc(size, sizeof(int));

    pthread_create(&communicationThread, NULL, startCommunicationThread, 0);
    debug("jestem");
}

void finish() // dodać jakiś stan finish?
{
    //pthread_mutex_destroy( &stateMut);
    println("czekam na wątek \"komunikacyjny\"\n" );
    pthread_join(communicationThread, NULL);

    free(lastMessagePriorities);

    MPI_Type_free(&MPI_PAKIET_T);
    MPI_Finalize();
}

void sendPacket(int val, int destination, int msgType)
{
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->source = rank;
    pkt->ts = incrementLamport();
    pkt->value = val;

    sleep(SEC_IN_STATE);

    MPI_Send(pkt, 1, MPI_PAKIET_T, destination, msgType, MPI_COMM_WORLD);

    free(pkt);
}

int sendPacketToAll(int val, int msgType)
{
    packet_t *pkt =  malloc(sizeof(packet_t));
    pkt->source = rank;
    pkt->ts = incrementLamport();
    pkt->value = val;

    int myTs = pkt->ts;

    sleep(SEC_IN_STATE);

    for (int destination = 0; destination < size; ++destination) 
    {
        if (destination != rank)
        {
            MPI_Send(pkt, 1, MPI_PAKIET_T, destination, msgType, MPI_COMM_WORLD);   
        }
    }

    free(pkt);
    return myTs;
}

int incrementLamport()
{
	pthread_mutex_lock(&lamportMut);
	lamportClock++;
	pthread_mutex_unlock(&lamportMut);

	return lamportClock;
}

void setMaxLamport(int newValue)
{
	pthread_mutex_lock(&lamportMut);
	lamportClock = (newValue > lamportClock) ? newValue : lamportClock;
	lamportClock++;
	pthread_mutex_unlock(&lamportMut);
}

void changeState(state_t newState)
{
    currentState = newState;
}

int main(int argc, char **argv)
{
    initialize(&argc, &argv); 
    mainLoop();          
    finish();
    return 0;
}

