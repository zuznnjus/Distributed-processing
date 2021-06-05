#include "data.h"

int teamMembers, brokenFighters, injuredMarines;

state_t currentState = Mission;
mission_type_t currentMission;
pub_nr_t pubNumber;

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

int updateBrokenFighters()
{
    int fighters = rand() % teamMembers + MIN_TEAM_MEMBERS; 

    pthread_mutex_lock(&brokenFightersMut);
    brokenFighters += fighters; 
    pthread_mutex_unlock(&brokenFightersMut);

    return fighters;
}

int updateInjuredMarines()
{
    int marines = rand() % teamMembers + MIN_TEAM_MEMBERS; 

    pthread_mutex_lock(&injuredMarinesMut);
    injuredMarines += marines; 
    pthread_mutex_unlock(&injuredMarinesMut);

    return marines;
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