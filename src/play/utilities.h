
#ifndef SRC_PLAY_UTILITIES_H_INCLUDED
#define SRC_PLAY_UTILITIES_H_INCLUDED

#include "../../libs/main.h"
#include "../structs.h"
#include "./tateti/main.h"

unsigned char checkPlayerName(char *_name);

unsigned char formatPlayerName(char *_name);

unsigned char requestPlayerNames(SList *players);

void isPlayerReady();

void requestPlayerName(char *name);

#endif  // SRC_PLAY_UTILITIES_H_INCLUDED
