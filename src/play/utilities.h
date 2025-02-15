
#ifndef SRC_PLAY_UTILITIES_H_INCLUDED
#define SRC_PLAY_UTILITIES_H_INCLUDED

#include "../../libs/main.h"
#include "../structs.h"
#include "./tateti/main.h"

unsigned char requestPlayerNames(List* players);

int playGame(Player* player);

void isPlayerReady();

#endif  // SRC_PLAY_UTILITIES_H_INCLUDED
