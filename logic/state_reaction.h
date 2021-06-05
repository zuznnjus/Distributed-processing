#ifndef STATE_REACTION_H
#define STATE_REACTION_H

int missionStateReaction();

void waitWorkshopStateReaction(int);
void waitHospitalStateReaction(int);
void waitPubOneStateReaction();
void waitPubTwoStateReaction();

void inWorkshopStateReaction(int);
void inHospitalStateReaction(int);
void inPubOneStateReaction();
void inPubTwoStateReaction();

#endif