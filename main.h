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

#include "model/data.h"

/* odkomentować, jeżeli się chce DEBUGI */
//#define DEBUG 

extern int rank;
extern int size;

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

#define println(FORMAT, ...) printf("%c[%d;%dm [tid %d ts %d]:" FORMAT "%c[%d;%dm\n",  27, (1+(rank/7))%2, 31+(6+rank)%7, rank, lamportClock, ##__VA_ARGS__, 27,0,37);

void sendPacket(packet_t*, int, int);
void sendPacketToAll(int, int);
void changeState(state_t);

/* WaitQueue_j (poczatkowo pusta, wiec brak pierwszego node) */
int firstNodeHospital;
int firstNodeWorkshop;
int firstNodePubOne;
int firstNodePubTwo;

/* N-elementowa tablica zawierajaca zegar lamporta ostatniej wiadomosci od wszystkich innych procesow */
int* lastMessagePriorities;
void updateLastMessagePriorities(int, int);

extern int reqSumHosptial;
extern int reqSumWorkshop;
extern int reqSumPubOne;
extern int reqSumPubTwo;

#endif
