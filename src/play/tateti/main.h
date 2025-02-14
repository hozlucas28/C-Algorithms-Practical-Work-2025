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

// TURNS OF THE PLAYERS
#define NEXT 1
#define WAIT 0

//
#define NORMAL_DIAG 1
#define SECOND_DIAG 0



typedef struct {
    int whowon;
    int draw;
    int movements;
} BoardAnalysis;

typedef struct {
    int raw;       // indicates if what raw is a winning-loosing movement
    int column;    // same
    int diagonal;  // 1 or 0, if its 1 normal diagonal, if its 0, secondary diagonal
    // is a winning-loosing movement
} Coordinates;

typedef struct {
    int winningMoves;
    Coordinates lastCCwin;
    int drawMoves;
    Coordinates lastCCdraw;
} DataAI;

//
struct IPlayer;
struct Board;

typedef int (*move)(struct IPlayer *player, struct Board *_board, int internalvalue);

typedef struct{
    char name[PLAYER_NAME_LENGTH];
    int points;
    char assignedForm;
    char _assignedForm;
    int turn;
    unsigned char isAI;
    move movement;
} IPlayer;

typedef struct Board{
    int array2D[3][3];
    int emptySpaces;
} Board;



#endif  // SRC__PLAY__TATETI_H_INCLUDED
