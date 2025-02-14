#include "./main.h"
#include <stdio.h>
#include "../../../libs/list/main.h"
#include "time.h"

int playComputer(struct IPlayer *_AI, struct Board *_board, int opponentValue);
int playPlayer(IPlayer *_player, Board *_board, int opponentValue);
int makeMove(struct IPlayer *_player, struct Board *_board, int opponentValue);

// utilities
int multiplyColumn(int **board, int columnToMultiply, int maxRaw);
int multiplyRaw(int **board, int columnToMultiply, int maxRaw);
int multiplySecondaryDiagonalInSquareMatrix(int **board, int maxColumn);
int multiplyDiagonalInSquareMatrix(int **board, int maxColumn);
void checkRaws(int **board, DataAI *datacomp, int winThis, int drawthis);
void checkColumns(int **board, DataAI *datacomp, int winThis, int drawthis);
void checkDiagonals(int **_board, DataAI *datacomp, int winThis, int drawthis);
void winMovement(int **board, DataAI *data, int aivalue);
void drawMovement(int **board, DataAI *data, int aivalue);
void insertInRaw(int **board, int rawToSearch, int aivalue);
void insertInColumn(int **board, int columnToSearch, int aivalue);
void insertInDiagonal(int **board, int aivalue);
void insertInSecondaryDiagonal(int **board, int aivalue);
void saveDrawCC(DataAI *data, int *raw, int *column, int *diagonal);

// CONSTRUCTORS
void boardConstructor(BoardAnalysis *board);
void playersConstructors(Player *player, Player *computer);
void DataComputerConstructor(DataAI *data);
void iPlayerConstructor(IPlayer *player, char *name, int isIA, int points);

// GETTERS
int getWhoWon(BoardAnalysis *board);
int getDraw(BoardAnalysis *board);
int getTotalMovements(BoardAnalysis *board);
int getPlayerTurn(IPlayer *player);
int getPlayerInternalAssignedForm(Player *player);
int **getArray2D(Board *board);
int getInternalForm(IPlayer *p);
int lastCcDrawRaw(DataAI *data);
int lastCcDrawColumn(DataAI *data);
int diagonalDrawValue(DataAI *data);
int lastCWinRaw(DataAI *data);
int lastCcWinColumn(DataAI *data);
int diagonalWinValue(DataAI *data);

// setters
void updateEmptySpaces(Board *_board);
void assignForm(IPlayer *p1, IPlayer *p2);
void increaseDrawMoves(DataAI *data);
// program
int playGame(Player *player) {
    int player01Won = 0, player02Won = 0;
    IPlayer AI, _player;
    List players;
    IPlayer player01;
    IPlayer player02;

    Board _board = {.array2D = {{DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE},
                                {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE},
                                {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE}},
                    .emptySpaces = 9

    };

    iPlayerConstructor(&AI, "AI", 1, 0);
    iPlayerConstructor(&_player, player->name, 0, player->points);

    newList(&players);

    if (!pushElement(&players, &AI, sizeof(AI))) return 0;
    if (!pushElement(&players, &_player, sizeof(_player))) return 0;

    randomSort(&players);  // [PJ, AI]

    if (!popElement(&players, &player01, sizeof(player01))) return 0;
    if (!popElement(&players, &player02, sizeof(player02))) return 0;

    assignForm(&player01, &player02);

    while (getEmptySpaces(&_board) > 0 && !player01Won && !player02Won) {
        player01Won = makeMove(&player01, &_board, player02._assignedForm);
        if (player01Won) break;

        player02Won = makeMove(&player02, &_board, player01._assignedForm);
        if (player02Won) break;
    }

    if (getEmptySpaces(&_board) == 0) printf("EMPATE");
    if (player01Won) printf("GANO PJ 01, %s", player01.name);
    if (player02Won) printf("GANO PJ 02 %s", player02.name);

    return 1;
}

int makeMove( IPlayer *_player,  Board *_board, int opponentValue) {
    return _player->movement(_player, _board, opponentValue);
}

int playPlayer(IPlayer *_player, Board *_board, int opponentValue) {return 0;}

int playComputer(IPlayer *_AI, Board *_board, int opponentValue) {
    DataAI _AIdata;

    DataComputerConstructor(&_AIdata);

    int winThis = getInternalForm(_AI) * getInternalForm(_AI);
    int drawThis = opponentValue * opponentValue;

    checkRaws(getArray2D(_board), &_AIdata, winThis, drawThis);
    checkColumns(getArray2D(_board), &_AIdata, winThis, drawThis);
    checkDiagonals(getArray2D(_board), &_AIdata, winThis, drawThis);

    if (_AIdata.winningMoves) {
        winMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        return 1;
    }  // make winner movement
    if (_AIdata.drawMoves) {
        drawMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }
    randomMovement(_board);
    updateEmptySpaces(_board);
    return 0;
}

void drawMovement(int **board, DataAI *data, int aivalue) {
    if (lastCcDrawRaw(data)) {
        insertInRaw(board, lastCcDrawRaw(data), aivalue);
        return;
    }
    if (lastCcDrawColumn(data)) {
        insertInColumn(board, lastCcDrawColumn(data), aivalue);
        return;
    }
    if (diagonalDrawValue(data) == NORMAL_DIAG) {
        insertInDiagonal(board, aivalue);
        return;
    }
    if (diagonalDrawValue(data) == SECOND_DIAG) {
        insertInSecondaryDiagonal(board, aivalue);
    }
    return;
}

void winMovement(int **board, DataAI *data, int aivalue) {
    if (lastCWinRaw(data)) {
        insertInRaw(board, lastCWinRaw(data), aivalue);
        return;
    }
    if (lastCcWinColumn(data)) {
        insertInColumn(board, lastCcWinColumn(data), aivalue);
        return;
    }
    if (diagonalWinValue(data) == NORMAL_DIAG) {
        insertInDiagonal(board, aivalue);
        return;
    }
    if (diagonalWinValue(data) == SECOND_DIAG) {
        insertInSecondaryDiagonal(board, aivalue);
    }
    return;
}

void insertInRaw(int **board, int rawToSearch, int aivalue) {
    int columniterator;
    for (columniterator = 0; columniterator < COLUMNS; columniterator++) {
        if (board[rawToSearch][columniterator] == DEFAULT_VALUE) {
            board[rawToSearch][columniterator] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInColumn(int **board, int columnToSearch, int aivalue) {
    int rawIterator;
    for (rawIterator = 0; rawIterator < RAWS; rawIterator++) {
        if (board[rawIterator][columnToSearch] == DEFAULT_VALUE) {
            board[rawIterator][columnToSearch] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInDiagonal(int **board, int aivalue) {
    int iterator;
    for (iterator = 0; iterator < RAWS; iterator++) {
        if (board[iterator][iterator] == DEFAULT_VALUE) {
            board[iterator][iterator] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInSecondaryDiagonal(int **board, int aivalue) {
    int iterator;
    for (iterator = 0; iterator < RAWS; iterator++) {
        if (board[iterator][(COLUMNS - 1 - iterator)] == DEFAULT_VALUE) {
            board[iterator][(COLUMNS - 1 - iterator)] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void checkDiagonals(int **_board, DataAI *datacomp, int winThis, int drawthis) {
    int result;
    result = multiplyDiagonalInSquareMatrix(_board, COLUMNS);

    if (result == winThis) {
        increaseWinningMoves(datacomp);
        saveWinCC(datacomp, NULL, NULL, NORMAL_DIAG);
    }

    if (result == drawthis) {
        increaseDrawMoves(datacomp);
        saveDrawCC(datacomp, NULL, NULL, NORMAL_DIAG);
    }

    result = multiplySecondaryDiagonalInSquareMatrix(_board, COLUMNS);

    if (result == winThis) {
        increaseWinningMoves(datacomp);
        saveWinCC(datacomp, NULL, NULL, SECOND_DIAG);
    }

    if (result == drawthis) {
        increaseDrawMoves(datacomp);
        saveDrawCC(datacomp, NULL, NULL, NORMAL_DIAG);
    }
    return;
}

void checkRaws(int **board, DataAI *datacomp, int winThis, int drawthis) {
    int result, rawiterator;

    for (rawiterator = 0; rawiterator < RAWS; rawiterator++) {
        result = multiplyRaw(board, rawiterator, COLUMNS);
        if (result == winThis) {
            increaseWinningMoves(datacomp);
            saveWinCC(datacomp, rawiterator, NULL, NULL);
        }
        if (result == drawthis) {
            increaseDrawMoves(datacomp);
            saveDrawCC(datacomp, rawiterator, NULL, NULL);
        }
    }
    return;
}

void checkColumns(int **board, DataAI *datacomp, int winThis, int drawthis) {
    int result, columnIterator;

    for (columnIterator = 0; columnIterator < COLUMNS; columnIterator++) {
        result = multiplyColumn(board, columnIterator, RAWS);
        if (result == winThis) {
            increaseWinningMoves(datacomp);
            saveWinCC(datacomp, NULL, columnIterator, NULL);
        }
        if (result == drawthis) {
            increaseDrawMoves(datacomp);
            saveDrawCC(datacomp, NULL, columnIterator, NULL);
        }
    }
}

int multiplyRaw(int **board, int rawToMultiply, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[rawToMultiply][iterator];
    }
    return accumulator;
}

int multiplyColumn(int **board, int columnToMultiply, int maxRaw) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxRaw; iterator++) {
        accumulator *= board[iterator][columnToMultiply];
    }
    return accumulator;
}

int multiplyDiagonalInSquareMatrix(int **board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[iterator][iterator];
    }
    return accumulator;
}

int multiplySecondaryDiagonalInSquareMatrix(int **board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= board[iterator][(maxColumn - 1 - iterator)];
    }
    return accumulator;
}

// CONSTRUCTORS

void DataComputerConstructor(DataAI *data) {
    data->drawMoves = 0;
    data->lastCCdraw.column = NULL;
    data->lastCCdraw.diagonal = NULL;
    data->lastCCdraw.raw = NULL;
    data->lastCCwin.column = NULL;
    data->lastCCwin.diagonal = NULL;
    data->lastCCwin.raw = NULL;
    data->winningMoves = 0;
    return;
}

void iPlayerConstructor(IPlayer *player, char *name, int isIA, int points) {
    player->points = points;
    player->isAI = isIA;
    strcpy(player->name, name);
    if (isIA) player->_assignedForm = 3;
    player->movement = playComputer;
    return;
    player->_assignedForm = 2;
    player->movement = playPlayer;
    return;
}

// GETTERS
int getEmptySpaces(Board *_board) { return _board->emptySpaces; }
int **getArray2D(Board *board) { return board->array2D; }
int getInternalForm(Player *p) { return p->_assignedForm; }

int lastCcDrawRaw(DataAI *data) { return data->lastCCdraw.raw; }
int lastCcDrawColumn(DataAI *data) { return data->lastCCdraw.column; }
int diagonalDrawValue(DataAI *data) { return data->lastCCdraw.diagonal; }
int lastCWinRaw(DataAI *data) { return data->lastCCwin.raw; }
int lastCcWinColumn(DataAI *data) { return data->lastCCwin.column; }
int diagonalWinValue(DataAI *data) { return data->lastCCwin.diagonal; }

// SETTERS
void increaseWinningMoves(DataAI *data) { data->winningMoves += 1; }
void increaseDrawMoves(DataAI *data) { data->drawMoves += 1; }
void assignForm(Player *p1, Player *p2) {
    p1->assignedForm = 'X';
    p2->assignedForm = 'O';
}
void saveWinCC(DataAI *data, int * raw, int *column, int *diagonal) {
    if (raw != NULL) {
        data->lastCCwin.raw = *raw;
        return;
    }
    if (column != NULL) {
        data->lastCCwin.column = *column;
        return;
    }
    if (diagonal != NULL) data->lastCCwin.diagonal = *diagonal;
    return;
}
void saveDrawCC(DataAI *data, int raw, int column, int diagonal) {
    if (raw != NULL) {
        data->lastCCdraw.raw = *raw;
        return;
    }
    if (column != NULL) {
        data->lastCCdraw.column = *column;
        return;
    }
    if (diagonal != NULL) data->lastCCdraw.diagonal = *diagonal;
    return;
}
void updateEmptySpaces(Board *_board) {
    if (_board->emptySpaces > 0) _board->emptySpaces -= 1;
    return;
}
