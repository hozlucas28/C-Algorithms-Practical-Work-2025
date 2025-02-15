#include "../libs/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./configuration/main.h"
#include "./macros.h"
#include "./play/main.h"
#include "./show-ranking/main.h"
#include "./structs.h"

int main(const int argsLength, char* args[]) {
    unsigned char error;

    Configuration config;

    int userInput;

    error = getConfiguration(&config, CONFIGURATION_PATH);
    if (error) {
        printf("> Error! An error occurred on get the configuration.");
        return 1;
    };

    printf("> %s team - A Tic-Tac-Toe game developed with C...", DEVELOPMENT_TEAM);

    printf("\n\n> Available options:\n\n%s%s%s", " 1 - Play Tic-Tac-Toe.\n", " 2 - Show ranking.\n",
           " 0 - Exit.\n");

    printf("\n> Select an option: ");
    fflush(stdin);
    scanf("%d", &userInput);

    while (userInput != 0) {
        switch (userInput) {
            case 1:
                printf("\n> Team %s...\n\n", config.teamName);
                playTicTacToe(&config);
                break;
            case 2:
                showRanking(&config);
                break;
            default:
                printf("\n> Invalid option! Try again...");
        };

        printf("> Available options:\n\n%s%s%s", " 1 - Play Tic-Tac-Toe.\n", " 2 - Show ranking.\n",
               " 0 - Exit.\n");

        printf("\n> Select an option: ");
        fflush(stdin);
        scanf("%d", &userInput);
    };

    return 0;
}
