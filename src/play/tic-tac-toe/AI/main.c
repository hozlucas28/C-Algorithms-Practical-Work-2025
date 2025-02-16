
#include "./main.h"

#include "../board/main.h"

/* ------------------------------ Constructors ------------------------------ */

void newAI(AI *ai) {
    ai->__tieMoves = 0;
    ai->__lastCCTie.__col = DEFAULT_POSITION_VALUE;
    ai->__lastCCTie.__diagonal = DEFAULT_POSITION_VALUE;
    ai->__lastCCTie.__row = DEFAULT_POSITION_VALUE;
    ai->__lastCCWin.__col = DEFAULT_POSITION_VALUE;
    ai->__lastCCWin.__diagonal = DEFAULT_POSITION_VALUE;
    ai->__lastCCWin.__row = DEFAULT_POSITION_VALUE;
    ai->__winningMoves = 0;
}

/* ------------------------------- Destructors ------------------------------ */

void destroyAI(AI *ai) {}

/* --------------------------------- Getters -------------------------------- */

int getAIWinningMoves(AI *ai) { return ai->__winningMoves; }

int getAITieMoves(AI *ai) { return ai->__tieMoves; }

int getAILastCCWinRow(AI *ai) { return ai->__lastCCWin.__row; }

int getAILastCCWinCol(AI *ai) { return ai->__lastCCWin.__col; }

int getAILastCCWinDiagonal(AI *ai) { return ai->__lastCCWin.__diagonal; }

int getAILastCCTieRow(AI *ai) { return ai->__lastCCTie.__row; }

int getAILastCCTieCol(AI *ai) { return ai->__lastCCTie.__col; }

int getAILastCCTieDiagonal(AI *ai) { return ai->__lastCCTie.__diagonal; }

/* --------------------------------- Methods -------------------------------- */

void aiReadRows(AI *ai, Board *board, const int winThis, const int tieThis) {
    size_t i;

    const size_t boardRows = getBoardRows(board);
    const size_t boardCols = getBoardCols(board);

    int result;

    for (i = 0; i < boardRows; i++) {
        result = multiplyBoardRow(board, i, boardCols - 1);

        if (result == winThis) {
            ai->__winningMoves += 1;
            ai->__lastCCWin.__row = i;

        } else if (result == tieThis) {
            ai->__tieMoves += 1;
            ai->__lastCCTie.__row = i;
        }
    }
}

void aiReadCols(AI *ai, Board *board, const int winThis, const int tieThis) {
    size_t i;

    const size_t boardRows = getBoardRows(board);
    const size_t boardCols = getBoardCols(board);

    int result;

    for (i = 0; i < boardCols; i++) {
        result = multiplyBoardCol(board, i, boardRows - 1);

        if (result == winThis) {
            ai->__winningMoves += 1;
            ai->__lastCCWin.__col = i;
        } else if (result == tieThis) {
            ai->__tieMoves += 1;
            ai->__lastCCTie.__col = i;
        }
    }
}

void aiReadDiagonals(AI *ai, Board *board, const int winThis, const int tieThis) {
    int result;
    int mainDiagonal = MAIN_DIAGONAL_VALUE;
    int secondaryDiagonal = SECONDARY_DIAGONAL_VALUE;

    result = multiplyBoardMainDiagonal(board);

    if (result == winThis) {
        ai->__winningMoves += 1;
        ai->__lastCCWin.__diagonal = mainDiagonal;

    } else if (result == tieThis) {
        ai->__tieMoves += 1;
        ai->__lastCCTie.__diagonal = mainDiagonal;
    }

    result = multiplyBoardSecondaryDiagonal(board);

    if (result == winThis) {
        ai->__winningMoves += 1;
        ai->__lastCCWin.__diagonal = secondaryDiagonal;

    } else if (result == tieThis) {
        ai->__tieMoves += 1;
        ai->__lastCCTie.__diagonal = secondaryDiagonal;
    }
}
