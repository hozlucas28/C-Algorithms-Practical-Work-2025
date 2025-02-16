#ifndef SRC__PLAY__TICTACTOE__BOARD_H_INCLUDED
#define SRC__PLAY__TICTACTOE__BOARD_H_INCLUDED

#include <stdlib.h>

typedef struct Board {
    int **__array2D;
    size_t __rows;
    size_t __cols;
    size_t __cells;
    int __freeCells;
    int __cellDefaultValue;
} Board;

/* ------------------------------ Constructors ------------------------------ */

Board *newBoard(const size_t rows, const size_t cols, const int cellDefaultValue);

/* ------------------------------- Destructors ------------------------------ */

void destroyBoard(Board *board);

/* --------------------------------- Getters -------------------------------- */

int **getBoardArray2D(const Board *board);

size_t getBoardRows(const Board *board);

size_t getBoardCols(const Board *board);

int getBoardFreeCells(const Board *board);

unsigned char getBoardValue(const Board *board, const size_t row, const size_t col, int *value);

/* --------------------------------- Methods -------------------------------- */

int multiplyBoardCol(const Board *board, const size_t targetCol, const size_t stopAtRow);

int multiplyBoardMainDiagonal(const Board *board);

int multiplyBoardRow(const Board *board, const size_t targetRow, const size_t stopAtCol);

int multiplyBoardSecondaryDiagonal(const Board *board);

unsigned char boardHasAnyFreeCorner(const Board *board);

unsigned char insertBoardValue(Board *board, const size_t row, const size_t col, const int value);

unsigned char insertBoardValueInColFreeCell(Board *board, const size_t targetCol, const int value);

unsigned char insertBoardValueInMainDiagonalFreeCell(Board *board, const int value);

unsigned char insertBoardValueInRowFreeCell(Board *board, const size_t targetRow, const int value);

unsigned char insertBoardValueInSecondaryDiagonalFreeCell(Board *board, const int value);

unsigned char isBoardCenterFree(const Board *board);

unsigned char isBoardPositionFree(const Board *board, const size_t row, const size_t col);

unsigned char isColsBoardWinningValue(const Board *board, const int winningValue);

unsigned char isDiagonalsBoardWinningValue(const Board *board, const int winningValue);

unsigned char isRowsBoardWinningValue(const Board *board, const int winningValue);

unsigned char insertInFirstFreeBoardCorner(Board *board, const int value);

unsigned char rndBoardInsert(Board *board, const int value);

#endif  // SRC__PLAY__TICTACTOE__BOARD_H_INCLUDED
