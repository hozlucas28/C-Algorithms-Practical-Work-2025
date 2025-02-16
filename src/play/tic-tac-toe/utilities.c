
#include "./utilities.h"

#include <math.h>
#include <stdio.h>

#include "../../player/main.h"
#include "./AI/main.h"
#include "./board/main.h"

/* ---------------------------- Private Functions --------------------------- */

void __aiWinningMove(Board *board, AI *ai, int aiAssignedFormValue);

void __aiTyingMove(Board *board, AI *ai, int aiAssignedFormValue);

/* ---------------------------- Public Functions ---------------------------- */

void showBoard(Board *board, Player *player01, Player *player02) {
    const size_t boardRows = getBoardRows(board);
    const size_t boardCols = getBoardCols(board);

    const int leftPadding = 2;
    const size_t topAndEndLineLength = boardCols * 3 + boardCols - 2;

    int i;
    int j;

    int boardValue;
    char boardValueRepr;

    printf("%-*s+", leftPadding, " ");
    for (i = 0; i <= topAndEndLineLength; i++) printf("-");
    puts("+");

    for (i = 0; i < boardRows; i++) {
        printf("%-*s|", leftPadding, " ");

        for (j = 0; j < boardCols; j++) {
            getBoardValue(board, i, j, &boardValue);

            if (boardValue == getPlayerAssignedFormValue(player01)) {
                boardValueRepr = getPlayerAssignedForm(player01);
            } else if (boardValue == getPlayerAssignedFormValue(player02)) {
                boardValueRepr = getPlayerAssignedForm(player02);
            } else {
                boardValueRepr = ' ';
            };

            printf(" %c |", boardValueRepr);
        }

        puts("");
    }

    printf("%-*s+", leftPadding, " ");
    for (i = 0; i <= topAndEndLineLength; i++) printf("-");
    puts("+\n");
}

unsigned char _playPlayer(Player *player, Board *board, int opponentAssignedFormValue) {
    int row;
    int col;

    int fieldsRead;

    int winningValue;

    printf("> In which position do you want to insert the \"%c\"? (Row / Column) ",
           getPlayerAssignedForm(player));
    fflush(stdin);
    fieldsRead = scanf("%d / %d", &row, &col);
    puts("");

    while (fieldsRead != 2 || row < 1 || row > getBoardRows(board) || col < 1 ||
           col > getBoardCols(board) || !isBoardPositionFree(board, row - 1, col - 1)) {
        puts("> Invalid position! Try again...\n");

        printf("> In which position do you want to insert the \"%c\"? (Row / Column) ",
               getPlayerAssignedForm(player));
        fflush(stdin);
        fieldsRead = scanf("%d / %d", &row, &col);
        puts("");
    };

    insertBoardValue(board, row - 1, col - 1, getPlayerAssignedFormValue(player));

    if (getBoardFreeCells(board) > 6) return 0;

    winningValue = pow(getPlayerAssignedFormValue(player), 3);

    return isRowsBoardWinningValue(board, winningValue) ||
           isColsBoardWinningValue(board, winningValue) ||
           isDiagonalsBoardWinningValue(board, winningValue);
}

void __aiWinningMove(Board *board, AI *ai, int aiAssignedFormValue) {
    if (getAILastCCWinRow(ai) != DEFAULT_POSITION_VALUE) {
        insertBoardValueInRowFreeCell(board, getAILastCCWinRow(ai), aiAssignedFormValue);

    } else if (getAILastCCWinCol(ai) != DEFAULT_POSITION_VALUE) {
        insertBoardValueInColFreeCell(board, getAILastCCWinCol(ai), aiAssignedFormValue);

    } else if (getAILastCCWinDiagonal(ai) == MAIN_DIAGONAL_VALUE) {
        insertBoardValueInMainDiagonalFreeCell(board, aiAssignedFormValue);

    } else if (getAILastCCWinDiagonal(ai) == SECONDARY_DIAGONAL_VALUE) {
        insertBoardValueInSecondaryDiagonalFreeCell(board, aiAssignedFormValue);
    }
}

void __aiTyingMove(Board *board, AI *ai, int aiAssignedFormValue) {
    if (getAILastCCTieRow(ai) != DEFAULT_POSITION_VALUE) {
        insertBoardValueInRowFreeCell(board, getAILastCCTieRow(ai), aiAssignedFormValue);

    } else if (getAILastCCTieCol(ai) != DEFAULT_POSITION_VALUE) {
        insertBoardValueInColFreeCell(board, getAILastCCTieCol(ai), aiAssignedFormValue);

    } else if (getAILastCCTieDiagonal(ai) == MAIN_DIAGONAL_VALUE) {
        insertBoardValueInMainDiagonalFreeCell(board, aiAssignedFormValue);

    } else if (getAILastCCTieDiagonal(ai) == SECONDARY_DIAGONAL_VALUE) {
        insertBoardValueInSecondaryDiagonalFreeCell(board, aiAssignedFormValue);
    }
}

unsigned char _playAI(Player *ai, Board *board, int opponentAssignedFormValue) {
    AI _ai;

    int winThis;
    int tieThis;

    printf("> The AI inserts \"%c\"...\n\n", getPlayerAssignedForm(ai));

    if (getBoardFreeCells(board) > 6) {
        rndBoardInsert(board, getPlayerAssignedFormValue(ai));
        return 0;
    }

    newAI(&_ai);

    winThis = getPlayerAssignedFormValue(ai) * getPlayerAssignedFormValue(ai);
    tieThis = opponentAssignedFormValue * opponentAssignedFormValue;

    aiReadRows(&_ai, board, winThis, tieThis);
    aiReadCols(&_ai, board, winThis, tieThis);
    aiReadDiagonals(&_ai, board, winThis, tieThis);

    if (getAIWinningMoves(&_ai)) {
        __aiWinningMove(board, &_ai, getPlayerAssignedFormValue(ai));
        return 1;
    }

    if (getAITieMoves(&_ai)) {
        __aiTyingMove(board, &_ai, getPlayerAssignedFormValue(ai));

    } else if (boardHasAnyFreeCorner(board)) {
        insertInFirstFreeBoardCorner(board, getPlayerAssignedFormValue(ai));

    } else if (isBoardCenterFree(board)) {
        insertBoardValue(board, getBoardRows(board), getBoardCols(board),
                         getPlayerAssignedFormValue(ai));
    } else {
        rndBoardInsert(board, getPlayerAssignedFormValue(ai));
    }

    return 0;
}
