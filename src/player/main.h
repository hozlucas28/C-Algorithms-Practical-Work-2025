#ifndef SRC__PLAYER_H_INCLUDED
#define SRC__PLAYER_H_INCLUDED

#include "./macros.h"

typedef struct {
    char __name[PLAYER_NAME_LENGTH];
    int __points;
    int __gamesWon;
    int __lostGames;
    int __tiedGames;
} Player;

/* ------------------------------ Constructors ------------------------------ */

void newPlayer(Player *player, const char *name);

/* ------------------------------- Destructors ------------------------------ */

void destroyPlayer(Player *player);

/* --------------------------------- Getters -------------------------------- */

char *getPlayerName(Player *player);

int getPlayerPoints(Player *player);

int getPlayerGamesWon(Player *player);

int getPlayerLostGames(Player *player);

int getPlayerTiedGames(Player *player);

/* --------------------------------- Methods -------------------------------- */

void appendPlayerGamesWon(Player *player, int gamesWon);

void appendPlayerLostGames(Player *player, int lostGames);

void appendPlayerPoints(Player *player, int points);

void appendPlayerTiedGames(Player *player, int tiedGames);

#endif  // SRC__PLAYER_H_INCLUDED
