#include "./main.h"
#include <stdio.h>
#include "../../../libs/list/main.h"
#include "time.h"

int playComputer(IPlayer *_AI, Board *_board, int opponentValue);
int playPlayer(IPlayer *_player, Board *_board, int opponentValue);
int makeMove(IPlayer *_player, Board *_board, int opponentValue);
int CreateInt2DArray(Board* _board, int columns, int raws);
void printTicTacToe(int** _board, IPlayer* player01, IPlayer *player02);

// utilities
int multiplyColumn(int **_board, int columnToMultiply, int maxRaw);
int multiplyRaw(int **_board, int columnToMultiply, int maxRaw);
int multiplySecondaryDiagonalInSquareMatrix(int **_board, int maxColumn);
int multiplyDiagonalInSquareMatrix(int **_board, int maxColumn);
void checkRaws(int **_board, DataAI *datacomp, int winThis, int drawthis);
void checkColumns(int **_board, DataAI *datacomp, int winThis, int drawthis);
void checkDiagonals(int **_board, DataAI *datacomp, int winThis, int drawthis);
void winMovement(int **_board, DataAI *data, int aivalue);
void drawMovement(int **_board, DataAI *data, int aivalue);
void insertInRaw(int **_board, int rawToSearch, int aivalue);
void insertInColumn(int **_board, int columnToSearch, int aivalue);
void insertInDiagonal(int **_board, int aivalue);
void insertInSecondaryDiagonal(int **_board, int aivalue);
void randomMovement(int **_board, int valueToInsert);

// CONSTRUCTORS
void DataComputerConstructor(DataAI *data);
void iPlayerConstructor(IPlayer *player, char *name, int isIA, int points);
int boardConstuctor(Board * board);

// GETTERS
int **getArray2D(Board *board);
int getInternalForm(IPlayer *p);
int lastCcDrawRaw(DataAI *data);
int lastCcDrawColumn(DataAI *data);
int diagonalDrawValue(DataAI *data);
int lastCWinRaw(DataAI *data);
int lastCcWinColumn(DataAI *data);
int diagonalWinValue(DataAI *data);
int getEmptySpaces(Board *_board);
char getExternalForm(IPlayer *p);
int getWinnigMoves(DataAI * data);
int getDrawMoves(DataAI * data);
char * getNamePlayer(IPlayer* p);

// setters
void updateEmptySpaces(Board *_board);
void assignForm(IPlayer *p1, IPlayer *p2);
void increaseDrawMoves(DataAI *data);
void increaseWinningMoves(DataAI *data);
void saveWinCC(DataAI *data, int * raw, int *column, int *diagonal);
void saveDrawCC(DataAI *data, int *raw, int *column, int *diagonal);
// program
int playGame(Player *player) {
    int player01Won = 0, player02Won = 0;
    IPlayer AI, _player;
    List players;
    IPlayer player01;
    IPlayer player02;
    Board _board;
    if(!boardConstuctor(&_board))
        return 0;


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
        player01Won = makeMove(&player01, &_board, getInternalForm(&player02));
        if (player01Won) break;

        printTicTacToe(getArray2D(&_board), &player01, &player02);

        player02Won = makeMove(&player02, &_board, getInternalForm(&player01));
        if (player02Won) break;

         printTicTacToe(getArray2D(&_board), &player01, &player02);
    }

    if (getEmptySpaces(&_board) == 0) printf("EMPATE");
    if (player01Won) printf("GANO PJ 01, %s", getNamePlayer(&player01));
    if (player02Won) printf("GANO PJ 02 %s", getNamePlayer(&player02));

    return 1;
}


//UTILITIES

void printTicTacToe(int** _board, IPlayer* player01, IPlayer *player02) {
    int i, j;

    printf("\n");
    puts("> TABLERO:");
    for (i = 0; i < RAWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf(" %c ",
                   _board[i][j] == DEFAULT_VALUE?
                   ' ' : (_board[i][j] == getInternalForm(player01))?
                   getExternalForm(player01) : getExternalForm(player02));
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int CreateInt2DArray(Board* _board, int columns, int raws)
{
    int **itertator, **freeiterator;
    int ** array = (int**)malloc(raws * sizeof(void*));
    if(!array)
        return 0;

    for(itertator = array; itertator < array + columns; itertator ++)
    {
        *itertator = (int*)malloc(sizeof(int)*columns);
        if(!*itertator)
        {
            for(freeiterator = itertator; freeiterator >= array; freeiterator --)
            {
                free(*freeiterator);
            }
            free(freeiterator);
            return 0;
        }
    }
    _board ->array2D = array;
    return 1;
}

int makeMove(IPlayer *_player,  Board *_board, int opponentValue) {
    move func = (move)_player->func_movement;
    return func(_player, _board, opponentValue);
}

int playPlayer(IPlayer *_player, Board *_board, int opponentValue) {return 0;}

int playComputer(IPlayer *_AI, Board *_board, int opponentValue) {
    DataAI _AIdata;

    DataComputerConstructor(&_AIdata);

    int winThis = getInternalForm(_AI) * getInternalForm(_AI);
    int drawThis = opponentValue * opponentValue;

    checkRaws( getArray2D(_board), &_AIdata, winThis, drawThis);
    checkColumns( getArray2D(_board), &_AIdata, winThis, drawThis);
    checkDiagonals( getArray2D(_board), &_AIdata, winThis, drawThis);

    if (getWinnigMoves(&_AIdata)) {
        winMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        return 1;
    }  // make winner movement
    if (getDrawMoves(&_AIdata)) {
        drawMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }
    randomMovement(getArray2D(_board), getInternalForm(_AI));
    updateEmptySpaces(_board);
    return 0;
}

void randomMovement(int **_board, int valueToInsert)
{
    int positionRaw, positionColumn;

    srand(time(NULL));

    positionRaw = rand() % RAWS;
    positionColumn = rand() % COLUMNS;

    while(_board[positionRaw][positionColumn] != DEFAULT_VALUE)
    {
        positionRaw = rand() % RAWS;
        positionColumn = rand() % COLUMNS;
    }

    _board[positionRaw][positionColumn] = valueToInsert;
    return ;
}

void drawMovement(int **_board, DataAI *data, int aivalue) {
    if (lastCcDrawRaw(data)) {
        insertInRaw(_board, lastCcDrawRaw(data), aivalue);
        return;
    }
    if (lastCcDrawColumn(data)) {
        insertInColumn(_board, lastCcDrawColumn(data), aivalue);
        return;
    }
    if (diagonalDrawValue(data) == NORMAL_DIAG) {
        insertInDiagonal(_board, aivalue);
        return;
    }
    if (diagonalDrawValue(data) == SECOND_DIAG) {
        insertInSecondaryDiagonal(_board, aivalue);
    }
    return;
}

void winMovement(int **_board, DataAI *data, int aivalue) {
    if (lastCWinRaw(data)) {
        insertInRaw(_board, lastCWinRaw(data), aivalue);
        return;
    }
    if (lastCcWinColumn(data)) {
        insertInColumn(_board, lastCcWinColumn(data), aivalue);
        return;
    }
    if (diagonalWinValue(data) == NORMAL_DIAG) {
        insertInDiagonal(_board, aivalue);
        return;
    }
    if (diagonalWinValue(data) == SECOND_DIAG) {
        insertInSecondaryDiagonal(_board, aivalue);
    }
    return;
}

void insertInRaw(int **_board, int rawToSearch, int aivalue) {
    int columniterator;
    for (columniterator = 0; columniterator < COLUMNS; columniterator++) {
        if (_board[rawToSearch][columniterator] == DEFAULT_VALUE) {
            _board[rawToSearch][columniterator] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInColumn(int **_board, int columnToSearch, int aivalue) {
    int rawIterator;
    for (rawIterator = 0; rawIterator < RAWS; rawIterator++) {
        if (_board[rawIterator][columnToSearch] == DEFAULT_VALUE) {
            _board[rawIterator][columnToSearch] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInDiagonal(int **_board, int aivalue) {
    int iterator;
    for (iterator = 0; iterator < RAWS; iterator++) {
        if (_board[iterator][iterator] == DEFAULT_VALUE) {
            _board[iterator][iterator] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void insertInSecondaryDiagonal(int **_board, int aivalue) {
    int iterator;
    for (iterator = 0; iterator < RAWS; iterator++) {
        if (_board[iterator][(COLUMNS - 1 - iterator)] == DEFAULT_VALUE) {
            _board[iterator][(COLUMNS - 1 - iterator)] = aivalue;
            return;
        }
    }
    puts("how im here");
}

void checkDiagonals(int **_board, DataAI *datacomp, int winThis, int drawthis) {
    int result, normaldiag = NORMAL_DIAG, secondarydiag = SECOND_DIAG;
    result = multiplyDiagonalInSquareMatrix(_board, COLUMNS);

    if (result == winThis) {
        increaseWinningMoves(datacomp);
        saveWinCC(datacomp, NULL, NULL, &normaldiag);
    }

    if (result == drawthis) {
        increaseDrawMoves(datacomp);
        saveDrawCC(datacomp, NULL, NULL, &normaldiag);
    }

    result = multiplySecondaryDiagonalInSquareMatrix(_board, COLUMNS);

    if (result == winThis) {
        increaseWinningMoves(datacomp);
        saveWinCC(datacomp, NULL, NULL, &secondarydiag);
    }

    if (result == drawthis) {
        increaseDrawMoves(datacomp);
        saveDrawCC(datacomp, NULL, NULL, &secondarydiag);
    }
    return;
}

void checkRaws(int **_board, DataAI *datacomp, int winThis, int drawthis) {
    int result, rawiterator;

    for (rawiterator = 0; rawiterator < RAWS; rawiterator++) {
        result = multiplyRaw(_board, rawiterator, COLUMNS);
        if (result == winThis) {
            increaseWinningMoves(datacomp);
            saveWinCC(datacomp, &rawiterator, NULL, NULL);
        }
        if (result == drawthis) {
            increaseDrawMoves(datacomp);
            saveDrawCC(datacomp, &rawiterator, NULL, NULL);
        }
    }
    return;
}

void checkColumns(int **_board, DataAI *datacomp, int winThis, int drawthis) {
    int result, columnIterator;

    for (columnIterator = 0; columnIterator < COLUMNS; columnIterator++) {
        result = multiplyColumn(_board, columnIterator, RAWS);
        if (result == winThis) {
            increaseWinningMoves(datacomp);
            saveWinCC(datacomp, NULL, &columnIterator, NULL);
        }
        if (result == drawthis) {
            increaseDrawMoves(datacomp);
            saveDrawCC(datacomp, NULL, &columnIterator, NULL);
        }
    }
}

int multiplyRaw(int **_board, int rawToMultiply, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= _board[rawToMultiply][iterator];
    }
    return accumulator;
}

int multiplyColumn(int **_board, int columnToMultiply, int maxRaw) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxRaw; iterator++) {
        accumulator *= _board[iterator][columnToMultiply];
    }
    return accumulator;
}

int multiplyDiagonalInSquareMatrix(int **_board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= _board[iterator][iterator];
    }
    return accumulator;
}

int multiplySecondaryDiagonalInSquareMatrix(int **_board, int maxColumn) {
    int iterator;
    int accumulator = 1;
    for (iterator = 0; iterator < maxColumn; iterator++) {
        accumulator *= _board[iterator][(maxColumn - 1 - iterator)];
    }
    return accumulator;
}

// CONSTRUCTORS

void DataComputerConstructor(DataAI *data) {
    data->drawMoves = 0;
    data->lastCCdraw.column = DEF_VALUE_COORDINATES;
    data->lastCCdraw.diagonal = DEF_VALUE_COORDINATES;
    data->lastCCdraw.raw = DEF_VALUE_COORDINATES;
    data->lastCCwin.column = DEF_VALUE_COORDINATES;
    data->lastCCwin.diagonal = DEF_VALUE_COORDINATES;
    data->lastCCwin.raw = DEF_VALUE_COORDINATES;
    data->winningMoves = 0;
    return;
}

void iPlayerConstructor(IPlayer *player, char *name, int isIA, int points) {
    player->points = points;
    player->isAI = isIA;
    strcpy(player->name, name);
    if (isIA) player->_assignedForm = 3;
    player->func_movement = (void*)playComputer;
    return;
    player->_assignedForm = 2;
    player->func_movement = (void*)playPlayer;
    return;
}

int boardConstuctor(Board * board)
{
    if(!CreateInt2DArray(board, COLUMNS, RAWS))
        return 0;
    board->emptySpaces = 9;
    return 1;
}


// GETTERS
int getEmptySpaces(Board *_board) { return _board->emptySpaces; }
int** getArray2D(Board *board) { return board->array2D; }
int getInternalForm(IPlayer *p) { return p->_assignedForm; }
char getExternalForm(IPlayer *p) { return p->assignedForm; }
char * getNamePlayer(IPlayer* p) {return p->name;}

int lastCcDrawRaw(DataAI *data) { return data->lastCCdraw.raw; }
int lastCcDrawColumn(DataAI *data) { return data->lastCCdraw.column; }
int diagonalDrawValue(DataAI *data) { return data->lastCCdraw.diagonal; }
int lastCWinRaw(DataAI *data) { return data->lastCCwin.raw; }
int lastCcWinColumn(DataAI *data) { return data->lastCCwin.column; }
int diagonalWinValue(DataAI *data) { return data->lastCCwin.diagonal; }
int getWinnigMoves(DataAI * data){return data->winningMoves;}
int getDrawMoves(DataAI * data){return data->drawMoves;}

// SETTERS
void increaseWinningMoves(DataAI *data) { data->winningMoves += 1; }
void increaseDrawMoves(DataAI *data) { data->drawMoves += 1; }
void assignForm(IPlayer *p1, IPlayer *p2) {
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
void saveDrawCC(DataAI *data, int *raw, int *column, int *diagonal) {
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




