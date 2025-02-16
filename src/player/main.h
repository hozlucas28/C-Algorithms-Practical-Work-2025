#ifndef SRC__PLAYER_H_INCLUDED
#define SRC__PLAYER_H_INCLUDED

#include "../play/tic-tac-toe/board/main.h"
#include "./macros.h"

typedef struct Player {
    char __name[PLAYER_NAME_LENGTH];
    char __assignedForm;
    int __assignedFormValue;
    int __points;
    int __gamesWon;
    int __lostGames;
    int __tiedGames;
    unsigned char __isAI;
    unsigned char (*__playMethod)(struct Player *player, Board *board,
                                  const int opponentAssignedFormValue);
} Player;

/* ------------------------------ Constructors ------------------------------ */

void newPlayer(Player *player, const char *name);

/* ------------------------------- Destructors ------------------------------ */

void destroyPlayer(Player *player);

/* --------------------------------- Getters -------------------------------- */

char *getPlayerName(Player *player);

char getPlayerAssignedForm(Player *player);

int getPlayerAssignedFormValue(Player *player);

int getPlayerPoints(Player *player);

int getPlayerGamesWon(Player *player);

int getPlayerLostGames(Player *player);

int getPlayerTiedGames(Player *player);

unsigned char isPlayerAI(Player *player);

/* --------------------------------- Setters -------------------------------- */

void setPlayerAssignedForm(Player *player, const char newAssignedForm);

void setPlayerAssignedFormValue(Player *player, const int newAssignedFormValue);

void setPlayerAI(Player *player, const unsigned char isAI);

void setPlayerPlayMethod(Player *player,
                         unsigned char (*newPlayMethod)(Player *player, Board *board,
                                                        const int opponentAssignedFormValue));

/* --------------------------------- Methods -------------------------------- */

void appendPlayerGamesWon(Player *player, const int gamesWon);

void appendPlayerLostGames(Player *player, const int lostGames);

void appendPlayerPoints(Player *player, const int points);

void appendPlayerTiedGames(Player *player, const int tiedGames);

unsigned char playerPlay(Player *player, Board *board, const int opponentAssignedFormValue);

#endif  // SRC__PLAYER_H_INCLUDED
