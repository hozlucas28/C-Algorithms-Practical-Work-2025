
#ifndef SRC_STRUCTS_H_INCLUDED
#define SRC_STRUCTS_H_INCLUDED

#include <stdlib.h>

#include "./macros.h"

/* --------------------------------- Common --------------------------------- */

typedef struct {
    char name[DEVELOPMENT_TEAM_LENGTH];  // TODO: use a dynamic method.
} Team;

/* --------------------------------- Player --------------------------------- */

typedef struct {
    char name[PLAYER_NAME_LENGTH];  // TODO: use a dynamic method.
    int points;
    char assignedForm;
} Player;

typedef struct {
    char name[PLAYER_NAME_LENGTH];  // TODO: use a dynamic method.
    int points;
    char lastGamePlayed[PLAYER_LAST_GAME_PLAYED_LENGTH];  // TODO: use a dynamic method.
} APIPlayer;

#endif  // SRC_STRUCTS_H_INCLUDED
