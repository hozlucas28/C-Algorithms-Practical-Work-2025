
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

    do {
        printf("> Enter a player name (0 to exit): ");
        fflush(stdin);
        fgets(player.name, PLAYER_NAME_LENGTH, stdin);
        puts("");

        lineBreak = strrchr(player.name, '\n');
        if (lineBreak != NULL) *lineBreak = '\0';

        if (*(player.name) == '0') continue;
        if (!pushElement(players, &player, sizeof(player))) return 0;

    } while (*(player.name) != '0');

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

void playGame(Player* player) {
    /*
    int result;
    Player Machine;
    // this function will simulate a game
    // will assign the player form
    //WhoStart(&player->Turn, &Machine.Turn);  // we want to change this
    // this function will assign the turn to the player and the machine
    // is a random, we are going to represent the turn with 1:next, and 0:have to


    if the game has 9 turns
    turns = 9
    mientras - turns > 9
        if (machine.turn == 1) //doing this we dont lose the randomness of the game
            {
                machinePlay() Here we edit the turn to the opposite,
                    so the player can play (ex: turn 1, now 0)

            }
        else
            playerPlay() Here we edit the turn to the opposite,
                    so the machine can play (ex: turn 1, now 0)



    // will update the player remaining turns
    // and will update the player points

    if (result)
        puts("Game Over, U've lost, try again");
    else
        puts("Nice, you won, take care of your family, they may lose too");

    updatePlayerStatistics(player);
    */
}
