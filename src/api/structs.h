#ifndef SRC__API_STRUCTS_H_INCLUDED
#define SRC__API_STRUCTS_H_INCLUDED

#include "./macros.h"

typedef struct {
    char name[API_PLAYER_NAME_LENGTH];
    int points;
    char lastGamePlayed[API_PLAYER_LAST_GAME_PLAYED_LENGTH];
} APIPlayer;

#endif  // SRC__API_STRUCTS_H_INCLUDED
