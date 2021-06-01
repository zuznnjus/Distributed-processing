#include "data.h"
#include "time.h"

pthread_mutex_t lamportMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t stateMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t missionTypeMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pubNumberMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t teamMembersMut = PTHREAD_MUTEX_INITIALIZER; //musi być mutex? zmieniane tylko na początku
pthread_mutex_t brokenFightersMut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t injuredMarinesMut = PTHREAD_MUTEX_INITIALIZER;

void setTeamMembers()
{
    pthread_mutex_lock(&teamMembersMut);
    teamMembers = rand() % MAX_TEAM_MEMBERS + MIN_TEAM_MEMBERS; // jako parametry wejściowe może?
    pthread_mutex_unlock(&teamMembersMut);
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
    pthread_mutex_lock(&missionTypeMut);
    int randomMission = rand() % 2;

    if (randomMission == 0) {
        currentMission = Flying;
    } else {
        currentMission = Running;
    }

    pthread_mutex_unlock(&missionTypeMut);
}

void setPubNumber()
{
    pthread_mutex_lock(&pubNumberMut);
    int randomPub = rand() % 2;

    if (randomPub == 0) {
        pubNumber = PubOne;
    } else {
        pubNumber = PubTwo;
    }
    pthread_mutex_unlock(&pubNumberMut);
}