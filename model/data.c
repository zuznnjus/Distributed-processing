#include "data.h"
#include "time.h"

int teamMembers, brokenFighters, injuredMarines;

pthread_mutex_t lamportMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t brokenFightersMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t injuredMarinesMut = PTHREAD_MUTEX_INITIALIZER; 

int* lastMessagePriorities;

int *isInWorkshopQueue;
int *isInHospitalQueue;
int *isInPubOneQueue;
int *isInPubTwoQueue;

void setTeamMembers()
{
    teamMembers = rand() % MAX_TEAM_MEMBERS + MIN_TEAM_MEMBERS; // jako parametry wejściowe może?
}

void setBrokenFighters()
{
    pthread_mutex_lock(&brokenFightersMut);
    brokenFighters = rand() % teamMembers + MIN_TEAM_MEMBERS; 
    pthread_mutex_unlock(&brokenFightersMut);
}

void setInjuredMarines()
{
    pthread_mutex_lock(&injuredMarinesMut);
    injuredMarines = rand() % teamMembers + MIN_TEAM_MEMBERS; 
    pthread_mutex_unlock(&injuredMarinesMut);
}

void decrementBrokenFighters()
{
    pthread_mutex_lock(&brokenFightersMut);
    brokenFighters--;
    pthread_mutex_unlock(&brokenFightersMut);
}

void decrementInjuredMarines()
{
    pthread_mutex_lock(&injuredMarinesMut);
    injuredMarines--;
    pthread_mutex_unlock(&injuredMarinesMut);
}

void setMissionType()
{   
    int randomMission = rand() % 2;

    if (randomMission == 0) {
        currentMission = Flying;
    } else {
        currentMission = Running;
    }
}

void setPubNumber()
{
    int randomPub = rand() % 2;

    if (randomPub == 0) {
        pubNumber = PubOne;
    } else {
        pubNumber = PubTwo;
    }
}

void updateLastMessagePriorities(int rank, int priority)
{
    lastMessagePriorities[rank] = priority;
}