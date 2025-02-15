
#include "./main.h"

#include <string.h>

/* ------------------------------ Constructors ------------------------------ */

void newPlayer(Player *player, const char *name) {
    strcpy(player->__name, name);
    player->__points = 0;
    player->__gamesWon = 0;
    player->__lostGames = 0;
    player->__tiedGames = 0;
}

/* ------------------------------- Destroyers ------------------------------- */

void destroyPlayer(Player *player) {
    strcpy(player->__name, "NULL");
    player->__points = 0;
    player->__gamesWon = 0;
    player->__lostGames = 0;
    player->__tiedGames = 0;
}

/* --------------------------------- Getters -------------------------------- */

char *getPlayerName(Player *player) { return player->__name; }

int getPlayerPoints(Player *player) { return player->__points; }

int getPlayerGamesWon(Player *player) { return player->__gamesWon; }

int getPlayerLostGames(Player *player) { return player->__lostGames; }

int getPlayerTiedGames(Player *player) { return player->__tiedGames; }

/* --------------------------------- Methods -------------------------------- */

void appendPlayerGamesWon(Player *player, int gamesWon) { player->__gamesWon += gamesWon; }

void appendPlayerLostGames(Player *player, int lostGames) { player->__lostGames += lostGames; }

void appendPlayerPoints(Player *player, int points) { player->__points += points; }

void appendPlayerTiedGames(Player *player, int tiedGames) { player->__tiedGames += tiedGames; }
