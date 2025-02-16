
#include "./main.h"

#include <string.h>

#include "../play/tic-tac-toe/main.h"

// Private methods
unsigned char __emptyPlayMethod(Player *player, Board *board, const int opponentAssignedFormValue);

/* ------------------------------ Constructors ------------------------------ */

unsigned char __emptyPlayMethod(Player *player, Board *board, const int opponentAssignedFormValue) {
    return 0;
}

void newPlayer(Player *player, const char *name) {
    strcpy(player->__name, name);
    player->__assignedForm = ' ';
    player->__assignedFormValue = 0;
    player->__points = 0;
    player->__gamesWon = 0;
    player->__lostGames = 0;
    player->__tiedGames = 0;
    player->__isAI = 0;
    player->__playMethod = &__emptyPlayMethod;
}

/* ------------------------------- Destroyers ------------------------------- */

void destroyPlayer(Player *player) {
    strcpy(player->__name, "NULL");
    player->__assignedForm = ' ';
    player->__assignedFormValue = 0;
    player->__points = 0;
    player->__gamesWon = 0;
    player->__lostGames = 0;
    player->__tiedGames = 0;
    player->__isAI = 0;
    player->__playMethod = &__emptyPlayMethod;
}

/* --------------------------------- Getters -------------------------------- */

char *getPlayerName(Player *player) { return player->__name; }

char getPlayerAssignedForm(Player *player) { return player->__assignedForm; }

int getPlayerAssignedFormValue(Player *player) { return player->__assignedFormValue; }

int getPlayerPoints(Player *player) { return player->__points; }

int getPlayerGamesWon(Player *player) { return player->__gamesWon; }

int getPlayerLostGames(Player *player) { return player->__lostGames; }

int getPlayerTiedGames(Player *player) { return player->__tiedGames; }

unsigned char isPlayerAI(Player *player) { return player->__isAI; }

/* --------------------------------- Setters -------------------------------- */

void setPlayerAssignedForm(Player *player, const char newAssignedForm) {
    player->__assignedForm = newAssignedForm;
}

void setPlayerAssignedFormValue(Player *player, const int newAssignedFormValue) {
    player->__assignedFormValue = newAssignedFormValue;
}

void setPlayerAI(Player *player, const unsigned char isAI) { player->__isAI = isAI; }

void setPlayerPlayMethod(Player *player,
                         unsigned char (*newPlayMethod)(Player *player, Board *board,
                                                        const int opponentAssignedFormValue)) {
    player->__playMethod = newPlayMethod;
}

/* --------------------------------- Methods -------------------------------- */

void appendPlayerGamesWon(Player *player, const int gamesWon) { player->__gamesWon += gamesWon; }

void appendPlayerLostGames(Player *player, const int lostGames) {
    player->__lostGames += lostGames;
}

void appendPlayerPoints(Player *player, const int points) { player->__points += points; }

void appendPlayerTiedGames(Player *player, const int tiedGames) {
    player->__tiedGames += tiedGames;
}

unsigned char playerPlay(Player *player, Board *board, const int opponentAssignedFormValue) {
    return player->__playMethod(player, board, opponentAssignedFormValue);
}
