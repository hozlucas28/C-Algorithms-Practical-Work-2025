#include "./main.h"

#include <stdio.h>

#include "../../libs/main.h"
#include "../api/main.h"
#include "../configuration/main.h"
#include "../structs.h"
#include "./utilities.h"

unsigned char playTicTacToe(const Configuration* config, char* localFilePath) {
    List players;
    List playersAfterMatch;

    Player player;
    unsigned games = 0;

    newList(&players);
    newList(&playersAfterMatch);

    if (!requestPlayerNames(&players)) {
        printf("> Error! An error occurred on get player names.");
        return 0;
    };

    randomSort(&players);

    while (popElement(&players, &player, sizeof(player))) {
        printf("> Hi %s, now it's your turn to play...\n\n", player.name);

        games = config->gamesPerPlayer;
        while (games > 0) {
            printf("> %d games remaining...\n\n", games);

            isPlayerReady(&player);
            //playGame(&player);  //  TODO: agregar printf() ganaste/perdiste.

            games--;
        }

        printf("> You won/lose the match! Your final score is %d.\n\n", player.points);

        printf("> ");
        system("pause");
        puts("");

        if (!pushElement(&playersAfterMatch, &player, sizeof(player))) return 0;
    }

    if (postAPI(config, &playersAfterMatch)) {
        puts("> Error! An error occurred on post to the API.\n\n");

        destroyList(&players);
        destroyList(&playersAfterMatch);

        return 0;
    };

    if (createLocalRecord(config, &playersAfterMatch, localFilePath)) {
        puts("> Error! An error occurred on create local record.\n\n");

        destroyList(&players);
        destroyList(&playersAfterMatch);

        return 0;
    };

    return 1;
}
