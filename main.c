#include "main.h"
#include "threads/communication_thread.h"
#include "threads/main_thread.h"

//#include <pthread.h>

/* sem_init sem_destroy sem_post sem_wait */
//#include <semaphore.h>
/* flagi dla open */
//#include <fcntl.h>

state_t currentState = Mission;
mission_type_t currentMission;
pub_nr_t pubNumber;
int size, rank, teamMembers, brokenFighters, injuredMarines; 
int reqSumHosptial, reqSumWorkshop, reqSumPubOne, reqSumPubTwo; // tez mutexy???????????
int firstNodeHospital = TRUE, firstNodeWorkshop = TRUE, 
    firstNodePubOne = TRUE, firstNodePubTwo = TRUE; // tez mutexy???????????
int K = 20, W = 15, SZ = 15;    
MPI_Datatype MPI_PAKIET_T;
pthread_t communicationThread; //workshopThread, hospitalThread

int lamportClock;

void check_thread_support(int provided)
{
    printf("THREAD SUPPORT: chcemy %d. Co otrzymamy?\n", provided);
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
            /* Potrzebne zamki wokół wywołań biblioteki MPI */
            printf("tylko jeden watek naraz może wykonać wołania do biblioteki MPI\n");
	        break;
        case MPI_THREAD_MULTIPLE: 
            printf("Pełne wsparcie dla wątków\n"); 
            break;
        default: 
            printf("Nikt nic nie wie\n");
    }
}

/* srprawdza, czy są wątki, tworzy typ MPI_PAKIET_T
*/
void initialize(int *argc, char ***argv)
{
    int provided;
    MPI_Init_thread(argc, argv, MPI_THREAD_MULTIPLE, &provided);
    check_thread_support(provided);

    /* Stworzenie typu */
    /* Poniższe (aż do MPI_Type_commit) potrzebne tylko, jeżeli
       brzydzimy się czymś w rodzaju MPI_Send(&typ, sizeof(pakiet_t), MPI_BYTE....
    */
    /* sklejone z stackoverflow */
    const int nitems = 3; /* bo packet_t ma trzy pola */
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
    srand(rank);

    setTeamMembers();
    lastMessagePriorities = (int *) malloc(sizeof(int) * TEAMS);

    pthread_create(&communicationThread, NULL, startCommunicationThread, 0);
    debug("jestem");
}

/* usunięcie zamków, czeka, aż zakończy się drugi wątek, zwalnia przydzielony typ MPI_PAKIET_T
   wywoływane w funkcji main przed końcem
*/
void finish() // dodać jakiś stan finish?
{
    pthread_mutex_destroy( &stateMut);
    /* Czekamy, aż wątek potomny się zakończy */
    println("czekam na wątek \"komunikacyjny\"\n" );
    pthread_join(communicationThread, NULL);

    MPI_Type_free(&MPI_PAKIET_T);
    MPI_Finalize();
}

void sendPacket(packet_t *pkt, int destination, int msgType)
{
    int freepkt = 0;

    if (pkt == 0) { 
        pkt = malloc(sizeof(packet_t)); 
        freepkt = 1;
    }

    pkt->source = rank;
    pkt->ts = incrementLamport();
    MPI_Send(pkt, 1, MPI_PAKIET_T, destination, msgType, MPI_COMM_WORLD);

    if (freepkt) {
        free(pkt);
    }
}

int incrementLamport()
{
	pthread_mutex_lock(&lamportMut);
	lamportClock++;
	int tmp = lamportClock; // dlaczegoooooooo
	pthread_mutex_unlock(&lamportMut);

	return lamportClock;
}

int setMaxLamport(int newValue)
{
	pthread_mutex_lock(&lamportMut);
	lamportClock = (newValue > lamportClock) ? newValue : lamportClock;
	lamportClock++;
	pthread_mutex_unlock(&lamportMut);

	return lamportClock;  // zwracamy czy void??????????
}

void changeState(state_t newState)
{
    pthread_mutex_lock(&stateMut);
    currentState = newState;
    pthread_mutex_unlock(&stateMut);
}

int main(int argc, char **argv)
{
    initialize(&argc, &argv); 
    mainLoop();          
    finish();
    return 0;
}

