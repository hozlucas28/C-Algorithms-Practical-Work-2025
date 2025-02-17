#ifndef SRC__PLAY__TICTACTOE__AI_H_INCLUDED
#define SRC__PLAY__TICTACTOE__AI_H_INCLUDED

#include "../board/main.h"
#include "./macros.h"

typedef struct {
    int __row;      /** Row where there is a winning move. */
    int __col;      /** Cow where there is a winning move. */
    int __diagonal; /**  1 if it's the main diagonal, or 0 if it's the secondary one. */
} Coordinates;

typedef struct {
    int __winningMoves;
    int __tieMoves;
    Coordinates __lastCCWin;
    Coordinates __lastCCTie;
} AI;

/* ------------------------------ Constructors ------------------------------ */

void newAI(AI *ai);

/* ------------------------------- Destructors ------------------------------ */

void destroyAI(AI *ai);

/* --------------------------------- Getters -------------------------------- */

int getAIWinningMoves(AI *ai);

int getAITieMoves(AI *ai);

int getAILastCCWinRow(AI *ai);

int getAILastCCWinCol(AI *ai);

int getAILastCCWinDiagonal(AI *ai);

int getAILastCCTieRow(AI *ai);

int getAILastCCTieCol(AI *ai);

int getAILastCCTieDiagonal(AI *ai);

/* --------------------------------- Methods -------------------------------- */

void aiReadRows(AI *ai, Board *board, const int winThis, const int tieThis);

void aiReadCols(AI *ai, Board *board, const int winThis, const int tieThis);

void aiReadDiagonals(AI *ai, Board *board, const int winThis, const int tieThis);

#endif  // SRC__PLAY__TICTACTOE__AI_H_INCLUDED
