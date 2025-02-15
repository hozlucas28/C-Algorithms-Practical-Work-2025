#ifndef SRC__PLAY__TATETI_H_INCLUDED
#define SRC__PLAY__TATETI_H_INCLUDED

#include "../../structs.h"
// LOCAL VALUES OF THE BOARD
#define VALUE_1 2
#define VALUE_2 3
#define DEFAULT_VALUE 1
// PROPERTIES: SIZE
#define RAWS 3
#define COLUMNS 3
//
#define NORMAL_DIAG 1
#define SECOND_DIAG 0
#define DEF_VALUE_COORDINATES -2

typedef struct {
    int raw;       // indicates in what raw is a winning-loosing movement
    int column;    // same but with column
    int diagonal;  // 1 or 0, if its 1 normal diagonal, if its 0, secondary diagonal
    // is a winning-loosing movement
} Coordinates;

typedef struct {
    int winningMoves;
    Coordinates lastCCwin;
    int drawMoves;
    Coordinates lastCCdraw;
} DataAI;

typedef struct {
    int raw, column;
} inputValuePlayer;

typedef struct Board {
    int **array2D;
    int emptySpaces;
} Board;

typedef struct IPlayer {
    char name[PLAYER_NAME_LENGTH];
    int points;
    char assignedForm;
    char _assignedForm;
    unsigned char isAI;
    // void *func_movement;
    int (*move)(struct IPlayer *player, Board *_board, int internalvalue);
} IPlayer;

// typedef int (*move)(IPlayer *player, Board *_board, int internalvalue);

int playGame(Player *player);

#endif  // SRC__PLAY__TATETI_H_INCLUDED
