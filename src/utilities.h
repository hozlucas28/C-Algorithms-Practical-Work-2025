
#ifndef SRC_UTILITIES_H_INCLUDED
#define SRC_UTILITIES_H_INCLUDED

#include "./structs.h"

void newPlayer(Player *player, char *name);
void addPlayerPoints(Player *player, int points);
void addPlayerGamesWons(Player *player);
void addPlayerLostGames(Player *player);
void addPlayerTiedGames(Player *player);

int cmpPlayersAscPoints(const void *playerA, const void *playerB);

#endif  // SRC_UTILITIES_H_INCLUDED
