#ifndef WORKSHOP_HOSPITAL_THREAD_H
#define WORKSHOP_HOSPITAL_THREAD_H

#define FIXED_FIGHTERS 1
#define CAPABLE_MARINES 1
#define SEC_IN_WORKSHOP_HOSPITAL 1

void *startWorkshopThread(void*);
void *startHospitalThread(void*);

#endif