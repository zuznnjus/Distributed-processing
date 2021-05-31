#ifndef SECTION_H
#define SECTION_H

int canEnterWorkshop();
int canEnterHospital();
int canEnterPubOne();
int canEnterPubTwo();

void putInLastMessagePriorities();
void putInWorkshopWaitQueue();
void putInHospitalWaitQueue();
void putInPubOneWaitQueue();
void putInPubTwoWaitQueue();

#endif