
#ifndef SRC_STRUCTS_H_INCLUDED
#define SRC_STRUCTS_H_INCLUDED

#include <stdlib.h>

#include "./macros.h"

/* --------------------------------- Player --------------------------------- */

typedef struct {
    char name[PLAYER_NAME_LENGTH];
    int points;
    int gamesWons;
    int lostGames;
    int tiedGames;
} Player;

typedef struct {
    char name[PLAYER_NAME_LENGTH];
    int points;
    char lastGamePlayed[PLAYER_LAST_GAME_PLAYED_LENGTH];
} APIPlayer;

#endif  // SRC_STRUCTS_H_INCLUDED
