#ifndef SRC__PLAY_STRUCTS_H_INCLUDED
#define SRC__PLAY_STRUCTS_H_INCLUDED

#include "../../libs/main.h"
#include "../configuration/structs.h"
#include "../structs.h"

typedef struct {
    Player winner;
    Player loser;
    unsigned char result;
    Configuration* configuration;
} Game;

typedef struct {
    SList* players;
    SList* games;
} TicTacToeGame;

#endif  // SRC__PLAY_STRUCTS_H_INCLUDED
