
#ifndef SRC_PLAY_UTILITIES_H_INCLUDED
#define SRC_PLAY_UTILITIES_H_INCLUDED

#include "../../libs/main.h"
#include "../structs.h"

unsigned char requestPlayerNames(List* players);

void playGame(Player* player);

void isPlayerReady();

#endif  // SRC_PLAY_UTILITIES_H_INCLUDED
