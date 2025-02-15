
#include "./utilities.h"

#include <stdio.h>
#include <string.h>

#include "./structs.h"

void newPlayer(Player *player, char *name) {
    strcpy(player->name, name);
    player->points = 0;
    player->gamesWons = 0;
    player->lostGames = 0;
    player->tiedGames = 0;
}

void addPlayerPoints(Player *player, int points) { player->points += points; }
void addPlayerGamesWons(Player *player) { player->gamesWons += 1; }
void addPlayerLostGames(Player *player) { player->lostGames += 1; }
void addPlayerTiedGames(Player *player) { player->tiedGames += 1; }
