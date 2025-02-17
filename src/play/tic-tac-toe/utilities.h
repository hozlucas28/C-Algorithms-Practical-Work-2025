#ifndef SRC__PLAY__TICTACTOE_UTILITIES_H_INCLUDED
#define SRC__PLAY__TICTACTOE_UTILITIES_H_INCLUDED

#include "../../player/main.h"
#include "./board/main.h"

void showBoard(Board *board, Player *player01, Player *player02);

unsigned char _playPlayer(Player *player, Board *board, const int opponentAssignedFormValue);

unsigned char _playAI(Player *ai, Board *board, const int opponentAssignedFormValue);

#endif  // SRC__PLAY__TICTACTOE_UTILITIES_H_INCLUDED
