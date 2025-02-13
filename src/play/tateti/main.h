#ifndef SRC__PLAY__TATETI_H_INCLUDED
#define SRC__PLAY__TATETI_H_INCLUDED

#include "../../structs.h"
#define VALUE_1 2
#define VALUE_2 3
#define DEFAULT_VALUE 1
#define NEXT 1
#define WAIT 0
#define RAWS 3
#define COLUMNS 3

typedef struct {
    int whowon;
    int draw;
    int movements;
} BoardAnalysis;

typedef struct {
    int raw;       // indicates in that raw is a winning-loosing movement
    int column;    // same
    int diagonal;  // 1 or 0, if its 1 normal diagonal, if its 0, secondary diagonal
    // is a winning-loosing movement
} Coordinates;

#define NORMAL_DIAG 1
#define SECOND_DIAG 0

typedef struct {
    int winningMoves;
    Coordinates lastCCwin;
    int drawMoves;
    Coordinates lastCCdraw;
} DataComputer;

void playGame(Player* player);

#endif  // SRC__PLAY__TATETI_H_INCLUDED
