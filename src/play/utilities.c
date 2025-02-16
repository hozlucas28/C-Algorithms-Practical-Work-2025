
#include "./utilities.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../../libs/main.h"
#include "../macros.h"
#include "../structs.h"
#include "../utilities.h"

unsigned char formatPlayerName(char *_name) {
    char *linepointer;

    linepointer = strrchr(_name, '\0');
    if (linepointer == NULL) return 0;
    linepointer--;
    while (!isalpha(*linepointer) && linepointer > _name) {
        linepointer--;
    }
    *(linepointer + 1) = '\0';
    return 1;
}

unsigned char checkPlayerName(char *_name) {
    char *lineBreak;

    lineBreak = strrchr(_name, '\n');

    if (lineBreak == NULL) return 0;
    *lineBreak = '\0';

    if (*lineBreak == '0') return 0;

    if (isspace(*_name) || *_name == '\0') {
        printf("> Name is required.\n\n");
        return 0;
    }
    return 1;
}

void requestPlayerName(char *name) {
    printf("> Enter a player name (0 to exit): ");
    do {
        fflush(stdin);
        fgets(name, PLAYER_NAME_LENGTH, stdin);
        fflush(stdin);
        puts("");

    } while (!checkPlayerName(name));
    return;
}

unsigned char requestPlayerNames(SList *players) {
    Player player;
    char playerName[PLAYER_NAME_LENGTH];

    requestPlayerName(playerName);
    formatPlayerName(playerName);
    if (*playerName == '0') return 0;

    newPlayer(&player, playerName);

    if (!pushSListElement(players, &player, sizeof(player))) return 0;

    while (*playerName != '0') {
        requestPlayerName(playerName);
        formatPlayerName(playerName);

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
