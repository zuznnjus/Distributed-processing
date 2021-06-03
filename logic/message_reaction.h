#ifndef MESSAGE_REACTION_H
#define MESSAGE_REACTION_H

#include "../main.h"

void reqWorkshopReaction(packet_t);
void reqHospitalReaction(packet_t);
void reqPubOneReaction(packet_t);
void reqPubTwoReaction(packet_t);

void ackWorkshopReaction(packet_t);
void ackHospitalReaction(packet_t);
void ackPubOneReaction(packet_t);
void ackPubTwoReaction(packet_t);

void releaseWorkshopReaction(packet_t);
void releaseHospitalReaction(packet_t);
void releasePubOneReaction(packet_t);
void releasePubTwoReaction(packet_t);

#endif