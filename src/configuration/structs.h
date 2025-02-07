
#ifndef SRC__CONFIG_STRUCTS_H_INCLUDED
#define SRC__CONFIG_STRUCTS_H_INCLUDED

#include "../macros.h"
#include "./macros.h"

typedef struct {
    char apiURL[MAXIMUM_API_URL_LENGTH];
    char teamName[TEAM_NAME_LENGTH];
    int gamesPerPlayer;
} Configuration;

#endif  // SRC__CONFIG_STRUCTS_H_INCLUDED
