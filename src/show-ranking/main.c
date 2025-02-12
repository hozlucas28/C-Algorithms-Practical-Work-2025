
#include "./main.h"

#include <stdio.h>
#include <string.h>

#include "../../libs/main.h"
#include "../api/main.h"
#include "../structs.h"

unsigned char __concatEndpoint(const char* base, const char* endpoint, char* store);

unsigned char showRanking(const Configuration* config) {
    unsigned char error = 1;
    char endpoint[MAXIMUM_API_URL_LENGTH];

    List players;
    size_t playersLength;

    int i;
    APIPlayer player;

    newList(&players);

    error = __concatEndpoint(config->apiURL, config->teamName, endpoint);
    if (!error) {
        printf("> Error! An error occurred on create endpoint.\n\n");
        return 0;
    }

    error = getAPI(endpoint, &players);
    if (!error) {
        printf("> Error! An error occurred on get players.\n\n");
        return 0;
    }

    sort(&players, &cmpPlayers);

    playersLength = getLength(&players);

    playersLength ? puts("")
                  : printf("\n> There are no players inside the %s team.\n", config->teamName);

    for (i = 0; i < playersLength; i++) {
        if (getElement(&players, &player, sizeof(player), i)) break;
        printf("> #%02d: [ %-*s | %06d points | %-*s (last game played) ]\n", i + 1,
               PLAYER_NAME_LENGTH, player.name, player.points, PLAYER_LAST_GAME_PLAYED_LENGTH,
               player.lastGamePlayed);
    };

    return 1;
}

unsigned char __concatEndpoint(const char* base, const char* endpoint, char* store) {
    strcpy(store, base);
    strcat(store, "/");
    strcat(store, endpoint);

    return 1;
}
