#include "./main.h"

#include <stdio.h>

#include "../../libs/main.h"
#include "../../utilities.h"
#include "../api/main.h"
#include "../configuration/main.h"
#include "../structs.h"
#include "../utilities.h"
#include "./tateti/main.h"
#include "./utilities.h"

unsigned char playTicTacToe(Configuration* config) {
    SList players;
    SList playersAfterMatch;

    Player player;

    unsigned games = 0;

    newSList(&players);
    newSList(&playersAfterMatch);

    if (!requestPlayerNames(&players)) {
        printf("> Error! An error occurred on get player names.\n\n");
        return 0;
    };

    randomSortSList(&players);

    while (popSListElement(&players, &player, sizeof(player))) {
        printf("> Hi %s, now it's your turn to play...\n\n", player.name);

        isPlayerReady(&player);

        games = config->gamesPerPlayer;
        while (games > 0) {
            printf("> %d games remaining...\n\n", games);

            playGame(&player);  //  TODO

            games--;
        }

        printf("> Your final score is %d.\n\n", player.points);

        if (!pushSListElement(&playersAfterMatch, &player, sizeof(player))) return 0;
    }

    selectionSortSList(&playersAfterMatch, &cmpPlayersAscPoints);

    if (postAPI(config, &playersAfterMatch)) {
        puts("> Error! An error occurred on post to the API.\n\n");

        destroySList(&players);
        destroySList(&playersAfterMatch);

        return 0;
    };

    puts("> The game statistics was sent to the API.\n");

    if (createLocalRecord(config, &playersAfterMatch)) {
        puts("> Error! An error occurred on create local record.\n\n");

        destroySList(&players);
        destroySList(&playersAfterMatch);

        return 0;
    };

    puts("> The game statistics was saved as a local report.\n");

    return 1;
}
