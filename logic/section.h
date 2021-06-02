#ifndef SECTION_H
#define SECTION_H

#include "../utils/priority_queue.h"
#include "../model/data.h"
#include "../main.h"

int reqSumWorkshop;
int reqSumHospital;
int reqSumPubOne;
int reqSumPubTwo;

extern node_t *startNodeWorkshopQueue;
extern node_t *startNodeHospitalQueue; 
extern node_t *startNodePubOneQueue; 
extern node_t *startNodePubTwoQueue;

pthread_mutex_t waitQueueWorkshopMut;
pthread_mutex_t waitQueueHospitalMut;
pthread_mutex_t waitQueuePubOneMut;
pthread_mutex_t waitQueuePubTwoMut;

void updateReqSumWorkshop(packet_t);
void updateReqSumHospital(packet_t);
void updateReqSumPubOne(packet_t);
void updateReqSumPubTwo(packet_t); 

int canEnterWorkshop();
int canEnterHospital();
int canEnterPubOne();
int canEnterPubTwo();

void putInWorkshopWaitQueue(packet_t);
void putInHospitalWaitQueue(packet_t);
void putInPubOneWaitQueue(packet_t);
void putInPubTwoWaitQueue(packet_t);

#endif