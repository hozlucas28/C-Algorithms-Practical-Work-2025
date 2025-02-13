#include "./main.h"
#include "time.h"
void __TurnRandomAllocator(Player *player, Player *computer);
int __multiplyColumn(int **board, int columnToMultiply, int maxRaw);
int __multiplyRaw(int **board, int columnToMultiply, int maxRaw);
int __multiplySecondaryDiagonalInSquareMatrix(int **board, int maxColumn);
int __multiplyDiagonalInSquareMatrix(int **board, int maxColumn);
void __PlayComputer(Player *computer, int **board, int ValuePlayer);
void __checkRaws(int **board, DataComputer *datacomp, int winThis, int drawthis);
void __checkColumns(int **board, DataComputer *datacomp, int winThis, int drawthis);
void __checkDiagonals(int **board, DataComputer *datacomp, int winThis, int drawthis);


void playGame(Player *player) {
    BoardAnalysis boardData;
    boardData.draw = 0;
    boardData.movements = 0;
    boardData.whowon = 0;

    Player computer;

    int board[RAWS][COLUMNS] = {{DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE},
                                {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE},
                                {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE}};

    __TurnRandomAllocator(player, &computer);

    player->_assignedForm = VALUE_1;
    computer._assignedForm = VALUE_2;

    while (!boardData.draw && !boardData.whowon) {
        if (player->turn == NEXT) {
            //PlayPlayer(player, board);
            // continue;
        }
        if (computer.turn == NEXT) {
            __PlayComputer(&computer, board, player->_assignedForm);
            // continue;
        }
        boardData.movements++;
    }
}

void __TurnRandomAllocator(Player *player, Player *computer) {
    srand(time(NULL));

    player->turn = rand() % (NEXT - WAIT + 1) + WAIT;  // rand () % (N-M+1) + M => N,M = ∃R ; N > M
    if (player->turn == NEXT)
        computer->turn = WAIT;
    else
        computer->turn = NEXT;
}

void __PlayComputer(Player *computer, int **board, int ValuePlayer)  // returns 1 if she wins
{
    DataComputer datacomp;

    int winThis = computer->_assignedForm * computer->_assignedForm;
    int drawThis = ValuePlayer * ValuePlayer;

    __checkRaws(board, &datacomp, winThis, drawThis);
    __checkColumns(board, &datacomp, winThis, drawThis);
    __checkDiagonals(board, &datacomp, winThis, drawThis);
}

void __checkDiagonals(int **board, DataComputer *datacomp, int winThis, int drawthis) {
    int result;
    result = __multiplyDiagonalInSquareMatrix(board, COLUMNS);

    if (result == winThis) {
        datacomp->winningMoves++;
        datacomp->lastCCwin.diagonal = NORMAL_DIAG;
    }

    if (result == drawthis) {
        datacomp->drawMoves++;
        datacomp->lastCCdraw.raw = NORMAL_DIAG;
    }
    result = __multiplySecondaryDiagonalInSquareMatrix(board, COLUMNS);

    if (result == winThis) {
        datacomp->winningMoves++;
        datacomp->lastCCwin.diagonal = SECOND_DIAG;
    }

    if (result == drawthis) {
        datacomp->drawMoves++;
        datacomp->lastCCdraw.raw = SECOND_DIAG;
    }
}

void __checkRaws(int **board, DataComputer *datacomp, int winThis, int drawthis) {
    int result, rawiterator;

    for (rawiterator = 0; rawiterator < RAWS; rawiterator++) {
        result = __multiplyRaw(board, rawiterator, COLUMNS);
        if (result == winThis) {
            datacomp->winningMoves++;
            datacomp->lastCCwin.raw = rawiterator;
        }
        if (result == drawthis) {
            datacomp->drawMoves++;
            datacomp->lastCCdraw.raw = rawiterator;
        }
    }
}
void __checkColumns(int **board, DataComputer *datacomp, int winThis, int drawthis) {
    int result, columnIterator;

    for (columnIterator = 0; columnIterator < COLUMNS; columnIterator++) {
        result = __multiplyColumn(board, columnIterator, RAWS);
        if (result == winThis) {
            datacomp->winningMoves++;
            datacomp->lastCCwin.column = columnIterator;
        }
        if (result == drawthis) {
            datacomp->drawMoves++;
            datacomp->lastCCdraw.column = columnIterator;
        }
    }
}

int __multiplyRaw(int **board, int rawToMultiply, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[rawToMultiply][iterator];
    }
    return accumulator;
}

int __multiplyColumn(int **board, int columnToMultiply, int maxRaw) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxRaw; iterator++) {
        accumulator *= board[iterator][columnToMultiply];
    }
    return accumulator;
}

int __multiplyDiagonalInSquareMatrix(int **board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[iterator][iterator];
    }
    return accumulator;
}

int __multiplySecondaryDiagonalInSquareMatrix(int **board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[iterator][(maxColumn - 1 - iterator)];
    }
    return accumulator;
}
