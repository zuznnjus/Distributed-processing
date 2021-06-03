#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* boolean */
#define TRUE 1
#define FALSE 0

#define SEC_IN_STATE 2

/* stany procesu */
typedef enum {Mission, WaitWorkshop, WaitHospital, WaitPubOne, WaitPubTwo, 
                    InWorkshop, InHospital, InPubOne, InPubTwo} state_t;

extern state_t currentState;

/* rozmiary sekcji krytycznych */ // parametry wejściowe!!!!!!!!!!!!!!!!!!!!!!!!
#define W 15
#define SZ 15
#define K 20

#define MIN_TEAM_MEMBERS 1
#define MAX_TEAM_MEMBERS 10

extern int teamMembers;
extern int brokenFighters;
extern int injuredMarines;

typedef enum {Flying, Running} mission_type_t;
extern mission_type_t currentMission;

typedef enum {PubOne, PubTwo} pub_nr_t;
extern pub_nr_t pubNumber;

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

#define ACK_VALUE 0

void setTeamMembers();
void setBrokenFighters();
void setInjuredMarines();
void setMissionType();
void setPubNumber();

void decrementBrokenFighters();
void decrementInjuredMarines();

extern pthread_mutex_t lamportMut;
extern pthread_mutex_t brokenFightersMut;
extern pthread_mutex_t injuredMarinesMut;

extern int *lastMessagePriorities;
void updateLastMessagePriorities(int, int);

extern int *isInWorkshopQueue;
extern int *isInHospitalQueue;
extern int *isInPubOneQueue;
extern int *isInPubTwoQueue;

#endif