#include "./main.h"

#include <stdio.h>

#include "../../libs/main.h"
#include "../api/main.h"
#include "../configuration/main.h"
#include "../structs.h"
#include "./utilities.h"

unsigned char playTicTacToe(const Configuration* config, const char* localFilePath) {
    unsigned char error;

    List players;
    List playersAfterMatch;

    Player player;
    unsigned games = 0;

    newList(&players);
    newList(&playersAfterMatch);

    requestPlayerNames(&players);

    randomSort(&players);

    while (popElement(&players, &player, sizeof(player))) {
        printf("> Hello %s, the game is about to start...\n\n", player.name);

        games = config->gamesPerPlayer;
        while (games > 0) {
            printf("> %d games remaining...\n\n", games);

            isPlayerReady(&player);
            playGame(&player);  //  TODO: agregar printf() ganaste/perdiste.

            games--;
        }

        printf("> You won/lose the match! Your final score is %d.\n\n", player.points);

        system("pause");

        puts("");

        if (!pushElement(&playersAfterMatch, &player, sizeof(player))) return 0;
    }

    error = postAPI(config, &playersAfterMatch);

    destroyList(&players);
    destroyList(&playersAfterMatch);

    if (error) {
        puts("> Error! An error occurred on post matches data.");
        return 0;
    };

    createLocalFile(&playersAfterMatch, localFilePath);

    return 1;
}
