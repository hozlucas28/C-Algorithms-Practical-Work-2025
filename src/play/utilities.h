
#ifndef SRC_PLAY_UTILITIES_H_INCLUDED
#define SRC_PLAY_UTILITIES_H_INCLUDED

#include "../../libs/main.h"

unsigned char requestPlayerNames(SList *players);

void isPlayerReady();

int cmpPlayersPointsAsc(const void *playerA, const void *playerB);

#endif  // SRC_PLAY_UTILITIES_H_INCLUDED
