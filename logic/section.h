#ifndef SECTION_H
#define SECTION_H

#include "../utils/priority_queue.h"
#include "../model/data.h"
#include "../main.h"

extern node_t *startNodeWorkshopQueue;
extern node_t *startNodeHospitalQueue; 
extern node_t *startNodePubOneQueue; 
extern node_t *startNodePubTwoQueue;

extern pthread_mutex_t waitQueueWorkshopMut;
extern pthread_mutex_t waitQueueHospitalMut;
extern pthread_mutex_t waitQueuePubOneMut;
extern pthread_mutex_t waitQueuePubTwoMut;

void updateWorkshopWaitQueueValues(packet_t);
void updateHospitalWaitQueueValues(packet_t);
void updatePubOneWaitQueueValues(packet_t);
void updatePubTwoWaitQueueValues(packet_t); 

int canEnterWorkshop();
int canEnterHospital();
int canEnterPubOne();
int canEnterPubTwo();
int canStartNewMission();

void putInWorkshopWaitQueue(packet_t);
void putInHospitalWaitQueue(packet_t);
void putInPubOneWaitQueue(packet_t);
void putInPubTwoWaitQueue(packet_t);

#endif