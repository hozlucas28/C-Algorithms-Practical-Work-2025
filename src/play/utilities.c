
#include <stdio.h>
#include <string.h>

#include "../../libs/main.h"
#include "../macros.h"
#include "../structs.h"

unsigned char requestPlayerNames(List* players) {
    char* lineBreak;

    Player player;

    player.points = 0;
    player.assignedForm = ' ';

    printf("> Enter a player name (0 to exit): ");
    fflush(stdin);
    fgets(player.name, PLAYER_NAME_LENGTH, stdin);
    puts("");

    lineBreak = strrchr(player.name, '\n');
    if (lineBreak != NULL) *lineBreak = '\0';

    if (*(player.name) == '0' || !pushElement(players, &player, sizeof(player))) return 0;

    while (*(player.name) != '0') {
        printf("> Enter a player name (0 to exit): ");
        fflush(stdin);
        fgets(player.name, PLAYER_NAME_LENGTH, stdin);
        puts("");

        lineBreak = strrchr(player.name, '\n');
        if (lineBreak != NULL) *lineBreak = '\0';

        if (*(player.name) == '0') break;
        if (!pushElement(players, &player, sizeof(player))) return 0;
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
