#include "../libs/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./configuration/main.h"
#include "./macros.h"
#include "./structs.h"
#include "./utilities.h"

int main(const int argsLength, char* args[]) {
    Configuration config;
    unsigned char error;

    Team team;

    int userInput;

    error = getConfiguration(&config, CONFIGURATION_PATH);
    if (error) {
        printf("> Error! An error occurred on get the configuration.");
        return 1;
    };

    // reprConfiguration(&config);
    // printf("\n");

    strcpy(team.name, config.teamName);

    printf("> %s team - A Tic-Tac-Toe game developed with C...", DEVELOPMENT_TEAM);

    printf("\n\n> Available options:\n\n%s%s%s", " 1 - Play Tic-Tac-Toe.\n", " 2 - Show ranking.\n",
           " 0 - Exit.\n");

    printf("\n> Select a option: ");
    scanf("%d", &userInput);

    while (userInput != 0) {
        switch (userInput) {
            case 1:
                printf("\n> Team %s...", team.name);
                printf("\n\n> [Playing Tic-Tac-Toe...]");
                break;
            case 2:
                printf("\n> [Showing ranking...]");
                break;
            default:
                printf("\n> [Invalid operation! Try again...]");
        };

        printf("\n\n> Available options:\n\n%s%s%s", " 1 - Play Tic-Tac-Toe.\n",
               " 2 - Show ranking.\n", " 0 - Exit.\n");

        printf("\n> Select a option: ");
        scanf("%d", &userInput);
    };

    return 0;
}
