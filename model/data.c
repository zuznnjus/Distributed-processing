#include "data.h"

int teamMembers, brokenFighters, injuredMarines;

state_t currentState = Mission;
mission_type_t currentMission;
pub_nr_t pubNumber;

pthread_mutex_t lamportMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fightersMarinesMut = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t sectionMut = PTHREAD_MUTEX_INITIALIZER; 

pthread_cond_t sectionCond = PTHREAD_COND_INITIALIZER; 
pthread_cond_t fightersMarinesCond = PTHREAD_COND_INITIALIZER; 

int* lastMessagePriorities;

int *isInWorkshopQueue;
int *isInHospitalQueue;
int *isInPubOneQueue;
int *isInPubTwoQueue;

int W = DEFAULT_W;
int SZ = DEFAULT_SZ;
int K = DEFAULT_K;
int MIN_TEAM_MEMBERS = DEFAULT_MIN_TEAM_MEMBERS;
int MAX_TEAM_MEMBERS = DEFAULT_MAX_TEAM_MEMBERS;

void setTeamMembers()
{
    teamMembers = rand() % MAX_TEAM_MEMBERS + MIN_TEAM_MEMBERS; 
}

int updateBrokenFighters()
{
    int fighters = rand() % teamMembers + MIN_TEAM_MEMBERS; 

    pthread_mutex_lock(&fightersMarinesMut);
    brokenFighters += fighters; 
    pthread_cond_signal(&fightersMarinesCond);
    pthread_mutex_unlock(&fightersMarinesMut);

    return fighters;
}

int updateInjuredMarines()
{
    int marines = rand() % teamMembers + MIN_TEAM_MEMBERS; 

    pthread_mutex_lock(&fightersMarinesMut);
    injuredMarines += marines; 
    pthread_cond_signal(&fightersMarinesCond);
    pthread_mutex_unlock(&fightersMarinesMut);

    return marines;
}

void decrementBrokenFighters()
{
    pthread_mutex_lock(&fightersMarinesMut);
    brokenFighters--;
    pthread_cond_signal(&fightersMarinesCond);
    pthread_mutex_unlock(&fightersMarinesMut);
}

void decrementInjuredMarines()
{
    pthread_mutex_lock(&fightersMarinesMut);
    injuredMarines--;
    pthread_cond_signal(&fightersMarinesCond);
    pthread_mutex_unlock(&fightersMarinesMut);
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