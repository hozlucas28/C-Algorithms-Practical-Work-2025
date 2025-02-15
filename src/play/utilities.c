
#include "./utilities.h"

#include <stdio.h>
#include <string.h>

#include "../../libs/main.h"
#include "../macros.h"
#include "../player/main.h"

unsigned char requestPlayerNames(SList *players) {
    char *lineBreak;

    Player player;
    char playerName[PLAYER_NAME_LENGTH];

    printf("> Enter a player name (0 to exit): ");
    fflush(stdin);
    fgets(playerName, PLAYER_NAME_LENGTH, stdin);
    puts("");

    lineBreak = strrchr(playerName, '\n');
    if (lineBreak != NULL) *lineBreak = '\0';

    if (*playerName == '0') return 0;

    newPlayer(&player, playerName);

    if (!pushSListElement(players, &player, sizeof(player))) return 0;

    while (*playerName != '0') {
        printf("> Enter a player name (0 to exit): ");
        fflush(stdin);
        fgets(playerName, PLAYER_NAME_LENGTH, stdin);
        puts("");

        lineBreak = strrchr(playerName, '\n');
        if (lineBreak != NULL) *lineBreak = '\0';

        if (*playerName == '0') break;

        newPlayer(&player, playerName);

        if (!pushSListElement(players, &player, sizeof(player))) return 0;
    };

    return 1;
}

void isPlayerReady() {
    char letter;

    do {
        printf("> Are you ready? (Y/N): ");
        fflush(stdin);
        scanf("%c", &letter);
        puts("");
    } while (letter != 'y' && letter != 'Y');
}

int cmpPlayersPointsAsc(const void *playerA, const void *playerB) {
    Player *_playerA = (Player *)playerA;
    Player *_playerB = (Player *)playerB;
    return getPlayerPoints(_playerB) - getPlayerPoints(_playerA);
}
