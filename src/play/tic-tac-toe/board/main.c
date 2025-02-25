
#include "./main.h"

#include <stdio.h>
#include <time.h>

#include "../macros.h"

/* ------------------------------ Constructors ------------------------------ */

Board *newBoard(const size_t rows, const size_t cols, const int cellDefaultValue) {
    Board *board;
    int **array2D;

    size_t i;
    size_t j;

    board = malloc(sizeof(Board));
    if (board == NULL) return NULL;

    array2D = malloc(rows * sizeof(int *));
    if (array2D == NULL) {
        free(board);
        return NULL;
    };

    for (i = 0; i < rows; i++) {
        *(array2D + i) = malloc(cols * sizeof(int));
        if (*(array2D + i) != NULL) continue;

        for (j = 0; j < i; i++) free(*(array2D + j));

        free(array2D);
        free(board);
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array2D[i][j] = cellDefaultValue;
        }
    }

    board->__array2D = array2D;
    board->__rows = rows;
    board->__cols = cols;
    board->__cells = rows * cols;
    board->__freeCells = rows * cols;
    board->__cellDefaultValue = cellDefaultValue;

    return board;
}

/* ------------------------------- Destructors ------------------------------ */

void destroyBoard(Board *board) {
    size_t i;

    for (i = 0; i < board->__rows; i++) free(*(board->__array2D + i));

    free(board->__array2D);
    free(board);
}

/* --------------------------------- Getters -------------------------------- */

int **getBoardArray2D(const Board *board) { return board->__array2D; }

size_t getBoardRows(const Board *board) { return board->__rows; }

size_t getBoardCols(const Board *board) { return board->__cols; }

int getBoardFreeCells(const Board *board) { return board->__freeCells; }

unsigned char getBoardValue(const Board *board, const size_t row, const size_t col, int *value) {
    if (row < 0 || row >= board->__rows) return 0;
    if (col < 0 || col >= board->__cols) return 0;

    *value = board->__array2D[row][col];

    return 1;
}

/* --------------------------------- Methods -------------------------------- */

int multiplyBoardCol(const Board *board, const size_t targetCol, const size_t stopAtRow) {
    int result = 1;

    size_t i;

    if (stopAtRow < 0 || stopAtRow > board->__rows) return 0;
    if (targetCol < 0 || targetCol > board->__cols) return 0;

    for (i = 0; i < stopAtRow; i++) result *= board->__array2D[i][targetCol];

    return result;
}

int multiplyBoardMainDiagonal(const Board *board) {
    int result = 1;

    size_t i;

    if (board->__rows != board->__cols) return 0;

    for (i = 0; i < board->__rows; i++) result *= board->__array2D[i][i];

    return result;
}

int multiplyBoardRow(const Board *board, const size_t targetRow, const size_t stopAtCol) {
    int result = 1;

    size_t i;

    if (targetRow < 0 || targetRow > board->__rows) return 0;
    if (stopAtCol < 0 || stopAtCol > board->__cols) return 0;

    for (i = 0; i < stopAtCol; i++) result *= board->__array2D[targetRow][i];

    return result;
}

int multiplyBoardSecondaryDiagonal(const Board *board) {
    int result = 1;

    int i;
    size_t j;

    if (board->__rows != board->__cols) return 0;

    for (i = board->__rows - 1; i >= 0; i--) {
        j = board->__cols - 1 - i;
        result *= board->__array2D[i][j];
    };

    return result;
}

unsigned char boardHasAnyFreeCorner(const Board *board) {
    if (board->__freeCells < 1) return 0;

    return board->__array2D[0][0] == board->__cellDefaultValue ||
           board->__array2D[0][board->__cols - 1] == board->__cellDefaultValue ||
           board->__array2D[board->__rows - 1][0] == board->__cellDefaultValue ||
           board->__array2D[board->__rows - 1][board->__cols - 1] == board->__cellDefaultValue;
}

unsigned char insertBoardValue(Board *board, const size_t row, const size_t col, const int value) {
    if (board->__freeCells < 1) return 0;

    if (row < 0 || row >= board->__rows) return 0;
    if (col < 0 || col >= board->__cols) return 0;

    board->__array2D[row][col] = value;
    board->__freeCells--;

    return 1;
}

unsigned char insertBoardValueInColFreeCell(Board *board, const size_t targetCol, const int value) {
    size_t i;

    if (targetCol < 0 || targetCol >= board->__cols) return 0;

    for (i = 0; i < board->__rows; i++) {
        if (board->__array2D[i][targetCol] != board->__cellDefaultValue) continue;

        board->__array2D[i][targetCol] = value;
        board->__freeCells--;
        return 1;
    }

    return 1;
}

unsigned char insertBoardValueInMainDiagonalFreeCell(Board *board, const int value) {
    size_t i;

    if (board->__rows != board->__cols) return 0;

    for (i = 0; i < board->__rows; i++) {
        if (board->__array2D[i][i] != board->__cellDefaultValue) continue;

        board->__array2D[i][i] = value;
        board->__freeCells--;
        return 1;
    }

    return 0;
}

unsigned char insertBoardValueInRowFreeCell(Board *board, const size_t targetRow, const int value) {
    size_t i;

    if (targetRow < 0 || targetRow >= board->__rows) return 0;

    for (i = 0; i < board->__cols; i++) {
        if (board->__array2D[targetRow][i] != board->__cellDefaultValue) continue;

        board->__array2D[targetRow][i] = value;
        board->__freeCells--;
        return 1;
    }

    return 0;
}

unsigned char insertBoardValueInSecondaryDiagonalFreeCell(Board *board, const int value) {
    int i;
    size_t j;

    if (board->__rows != board->__cols) return 0;

    for (i = board->__rows - 1; i >= 0; i--) {
        j = board->__cols - 1 - i;
        if (board->__array2D[i][j] != board->__cellDefaultValue) continue;

        board->__array2D[i][j] = value;
        board->__freeCells--;
        return 1;
    }

    return 0;
}

unsigned char isBoardCenterFree(const Board *board) {
    if (board->__rows != board->__cols) return 0;
    return board->__array2D[board->__rows - 1][board->__rows - 1] == board->__cellDefaultValue ? 1
                                                                                               : 0;
}

unsigned char isBoardPositionFree(const Board *board, const size_t row, const size_t col) {
    if (row < 0 || row >= board->__rows) return 0;
    if (col < 0 || col >= board->__cols) return 0;

    return board->__array2D[row][col] == board->__cellDefaultValue;
}

unsigned char isColsBoardWinningValue(const Board *board, const int winningValue) {
    int i;

    for (i = 0; i < board->__cols; i++) {
        if (multiplyBoardCol(board, i, board->__rows) == winningValue) return 1;
    }

    return 0;
}

unsigned char isDiagonalsBoardWinningValue(const Board *board, const int winningValue) {
    return multiplyBoardMainDiagonal(board) == winningValue ||
           multiplyBoardSecondaryDiagonal(board) == winningValue;
}

unsigned char isRowsBoardWinningValue(const Board *board, const int winningValue) {
    int i;

    for (i = 0; i < board->__rows; i++) {
        if (multiplyBoardRow(board, i, board->__cols) == winningValue) return 1;
    }

    return 0;
}

unsigned char insertInFirstFreeBoardCorner(Board *board, const int value) {
    if (board->__freeCells < 1) return 0;

    if (board->__array2D[0][0] == board->__cellDefaultValue) {
        board->__array2D[0][0] = value;
    } else if (board->__array2D[0][board->__cols - 1] == board->__cellDefaultValue) {
        board->__array2D[0][board->__cols - 1] = value;
    } else if (board->__array2D[board->__rows - 1][0] == board->__cellDefaultValue) {
        board->__array2D[board->__rows - 1][0] = value;
    } else if (board->__array2D[board->__rows - 1][board->__cols - 1] ==
               board->__cellDefaultValue) {
        board->__array2D[board->__rows - 1][board->__cols - 1] = value;
    }

    board->__freeCells--;

    return 1;
}

unsigned char rndBoardInsert(Board *board, const int value) {
    size_t rndRow;
    size_t rndCol;

    if (board->__freeCells < 1) return 0;

    srand(time(NULL));

    rndRow = rand() % board->__rows;
    rndCol = rand() % board->__cols;

    while (board->__array2D[rndRow][rndCol] != board->__cellDefaultValue) {
        rndRow = rand() % board->__rows;
        rndCol = rand() % board->__cols;
    }

    board->__array2D[rndRow][rndCol] = value;
    board->__freeCells--;

    return 1;
}
