#include "./play.h"

#include "../../libs/Stack/stack.h"
#include "../configuration/main.h"
#include "../structs.h"

int playTicTacToe(const Configuration* config) {
    tStack _ps;
    Player _player;
    unsigned games = 0;

    createStack(&_ps);

    AskNamesLoadIntoListAndMixItAndLoadIntoAStack(
        &_ps);  // this function will return the stack with the players mixed
    /* This name is not appropiate, now i dont have one better, but we need to change it

        We need to discuss how to do this, but the idea is to ask the names of the players nad load
       it into a some structure (list, array, etc), then mix it and load it into a stack (if its
       possible)
    */

    while (grabElementFromStack(&_ps, &_player, sizeof(_player)))
    // this function return 1 if its all ok, and 0 if the stack is empty
    {
        printf("Hello, Player %s, the game is about to star\n", _player.name);
        games = config->gamesPerPlayer;
        while (games > 0) {
            askPlayerIfHeIsReady(&_player);  // this function will interrogate
                                             // the player if he is ready
            playGame(&_player);

            games--;
            printf("\n %s, \n Your actual points are: %d \n", _player.name, _player.points);
            printf("Next game, %d: games left\n", games);
        }

        puts("You have finished your games");
        printf("%s, Your final points are: %d \n", _player.name, _player.points);
    }
    // we need to see how to manage it
    /*
            updateLocalFile(&_player, nameOfTheLocalFile);

                sendInformationToTheAPI(&_player);
                 this part of the code may change when we have the API, and how to do it
                 Also, im not sure if the function is void or int, so we will have to see it later
    */
    return 1;
}

void playGame(Player* player) {
    int result;
    Player Machine;
    // this function will simulate a game
    // will assign the player form
    WhoStart(&player->Turn, &Machine.Turn);  // we want to change this
    // this function will assign the turn to the player and the machine
    // is a random, we are going to represent the turn with 1:next, and 0:have to

    /*
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


    */
    // will update the player remaining turns
    // and will update the player points

    if (result)
        puts("Game Over, U've lost, try again");
    else
        puts("Nice, you won, take care of your family, they may lose too");

    updatePlayerStatistics(player);
}

void updateLocalFile(Player* player, char* nameOfTheLocalFile) {
    /*this function opens or creates a file to save the player information,
     in a local way.
     Doesnt matter the order, but its important to search the player (to update his profile)
     if he doesnt exist, insert at the end of the file.*/

    printf("Opening file %s \n", nameOfTheLocalFile);
    puts("The update is done!");
    puts("Closing the file");
}

void sendInformationToTheAPI(Player* Player) {
    // i dont know what to do here yet
}