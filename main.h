#ifndef GLOBALH
#define GLOBALH

#define _GNU_SOURCE
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/* odkomentować, jeżeli się chce DEBUGI */
//#define DEBUG 

/* boolean */
#define TRUE 1
#define FALSE 0

/* używane w wątku głównym, determinuje jak często i na jak długo zmieniają się stany */
#define STATE_CHANGE_PROB 50
#define SEC_IN_STATE 2

/* stany procesu */
typedef enum {Mission, WaitWorkshop, WaitHospital, WaitPubOne, WaitPubTwo, 
                    InWorkshop, InHospital, InPubOne, InPubTwo} state_t;

extern state_t currentState;
extern int rank;
extern int size;

/* Ile mamy członków zespołu, popsutych myśliwców i rannych? */
#define MIN_TEAM_MEMBERS 1
#define MAX_TEAM_MEMBERS 10
#define TEAMS 4 // parametry wejściowe!!!!!!!!!!!!!!!!!!!!!!!!

/* rozmiary sekcji krytycznych */ // parametry wejściowe!!!!!!!!!!!!!!!!!!!!!!!!
int W;
int SZ;
int K;

extern int teamMembers;
extern int brokenFighters;
extern int injuredMarines;

typedef enum {Flying, Running} mission_type_t;
extern mission_type_t currentMission;

/* zegar lamporta */
extern int lamportClock;
int incrementLamport();
int setMaxLamport(int); //???????????

/* to może przeniesiemy do global... */
typedef struct {
    int ts;       /* timestamp (zegar lamporta) */
    int source;      /* pole nie przesyłane, ale ustawiane w main_loop */
    int value;     /* wartosc popsutych mysliwosc/rannych marines - w wiadomosciach REQ, inaczej 0 */
} packet_t;

extern MPI_Datatype MPI_PAKIET_T;

/* Typy wiadomości */
#define REQ_WORKSHOP 1
#define REQ_HOSPITAL 2
#define REQ_PUB_ONE 3
#define REQ_PUB_TWO 4

#define ACK_WORKSHOP 5
#define ACK_HOSPITAL 6
#define ACK_PUB_ONE 7
#define ACK_PUB_TWO 8

#define RELEASE_WORKSHOP 9
#define RELEASE_HOSPITAL 10
#define RELEASE_PUB_ONE 11
#define RELEASE_PUB_TWO 12

/* macro debug - działa jak printf, kiedy zdefiniowano
   DEBUG, kiedy DEBUG niezdefiniowane działa jak instrukcja pusta 
   
   używa się dokładnie jak printfa, tyle, że dodaje kolorków i automatycznie
   wyświetla rank

   w związku z tym, zmienna "rank" musi istnieć.

   w printfie: definicja znaku specjalnego "%c[%d;%dm [%d]" escape[styl bold/normal;kolor [RANK]
                                           FORMAT:argumenty doklejone z wywołania debug poprzez __VA_ARGS__
					   "%c[%d;%dm"       wyczyszczenie atrybutów    27,0,37
                                            UWAGA:
                                                27 == kod ascii escape. 
                                                Pierwsze %c[%d;%dm ( np 27[1;10m ) definiuje styl i kolor literek
                                                Drugie   %c[%d;%dm czyli 27[0;37m przywraca domyślne kolory i brak pogrubienia (bolda)
                                                ...  w definicji makra oznacza, że ma zmienną liczbę parametrów
                                            
*/
#ifdef DEBUG
#define debug(FORMAT,...) printf("%c[%d;%dm [tid %d ts %d]:" FORMAT "%c[%d;%dm\n",  27, (1+(rank/7))%2, 31+(6+rank)%7, rank, lamportClock, ##__VA_ARGS__, 27,0,37);
#else
#define debug(...) ;
#endif

#define P_WHITE printf("%c[%d;%dm",27,1,37);
#define P_BLACK printf("%c[%d;%dm",27,1,30);
#define P_RED printf("%c[%d;%dm",27,1,31);
#define P_GREEN printf("%c[%d;%dm",27,1,33);
#define P_BLUE printf("%c[%d;%dm",27,1,34);
#define P_MAGENTA printf("%c[%d;%dm",27,1,35);
#define P_CYAN printf("%c[%d;%d;%dm",27,1,36);
#define P_SET(X) printf("%c[%d;%dm",27,1,31+(6+X)%7);
#define P_CLR printf("%c[%d;%dm",27,0,37);

/* printf ale z kolorkami i automatycznym wyświetlaniem RANK. Patrz debug wyżej po szczegóły, jak działa ustawianie kolorków */
#define println(FORMAT, ...) printf("%c[%d;%dm [tid %d ts %d]:" FORMAT "%c[%d;%dm\n",  27, (1+(rank/7))%2, 31+(6+rank)%7, rank, lamportClock, ##__VA_ARGS__, 27,0,37);

/* wysyłanie pakietu, skrót: wskaźnik do pakietu (0 oznacza stwórz pusty pakiet), do kogo, z jakim typem */
void sendPacket(packet_t*, int, int);
int setValue(int); 
void changeState(state_t);

void setTeamMembers();
void setBrokenFighters();
void setInjuredMarines();
void setMissionType();

void decrementBrokenFighters();
void decrementInjuredMarines();

/* WaitQueue_j (poczatkowo pusta, wiec brak pierwszego node) */
int firsNodeHospital;
int firsNodeWorkshop;
int firsNodePubOne;
int firsNodePubTwo;

/* N-elementowa tablica zawierajaca zegar lamporta ostatniej wiadomosci od wszystkich innych procesow */
int* lastMessagePriorities;

extern int reqSumHosptial;
extern int reqSumWorkshop;
extern int reqSumPubOne;
extern int reqSumPubTwo;

#endif
