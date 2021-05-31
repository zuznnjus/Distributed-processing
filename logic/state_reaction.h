#ifndef STATE_REACTION_H
#define STATE_REACTION_H

void missionStateReaction();

void waitWorkshopStateReaction();
void waitHospitalStateReaction();
void waitPubOneStateReaction();
void waitPubTwoStateReaction();

void inWorkshopStateReaction();
void inHospitalStateReaction();
void inPubOneStateReaction();
void inPubTwoStateReaction();

void sendPacketToAll(packet_t*, int);

#endif