#include "./main.h"

#include <stdio.h>
#include <time.h>

#include "../../../libs/main.h"
#include "../../configuration/main.h"
#include "../../utilities.h"

int playComputer(IPlayer *_AI, Board *_board, int opponentValue);
int playPlayer(IPlayer *_player, Board *_board, int opponentValue);
int makeMove(IPlayer *_player, Board *_board, int opponentValue);
int CreateInt2DArray(Board *_board, int columns, int raws);
void printTicTacToe(int **_board, IPlayer *player01, IPlayer *player02);

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
void playInCorner(int **_board, int valueToInsert);
unsigned char isThereAnyCorner(int **_board);
unsigned char isTheCenterFree(int **_board);
void playInCenter(int **_board, int valueToInsert);
unsigned char checkInputFormat(inputValuePlayer *datainput, char *_input);
void getValidatedInput(inputValuePlayer *datainput);
unsigned char IsThePositionFree(int **_board, inputValuePlayer *datainput);
unsigned char checkIfThePositionIsFree(int **_board, inputValuePlayer *datainput);
unsigned char checkTotalRaw(int **_board, int valueToWin);
unsigned char checkTotalColumn(int **_board, int valueToWin);
unsigned char checkTotalDiagonal(int **_board, int valueToWin);
unsigned char checkIfPlayerWon(int **_board, int userForm);
void showGameInformation(IPlayer *player01, IPlayer *player02);
void initializesArray2D(int **_2dArray, int value, int raws, int columns);

// CONSTRUCTORS
void DataComputerConstructor(DataAI *data);
void iPlayerConstructor(IPlayer *player, char *name, int isIA, int points);
int boardConstructor(Board *board);

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
int getWinnigMoves(DataAI *data);
int getDrawMoves(DataAI *data);
char *getNamePlayer(IPlayer *p);
int getDataInputRaw(inputValuePlayer *datainput);
int getDataInputColumn(inputValuePlayer *datainput);

// setters
void updateEmptySpaces(Board *_board);
void assignForm(IPlayer *p1, IPlayer *p2);
void increaseDrawMoves(DataAI *data);
void increaseWinningMoves(DataAI *data);
void saveWinCC(DataAI *data, int *raw, int *column, int *diagonal);
void saveDrawCC(DataAI *data, int *raw, int *column, int *diagonal);
void insertInIntArray2D(int **_array, int raw, int column, int value);

// program

int playGame(Player *player) {
    int player01Won = 0, player02Won = 0;
    IPlayer AI, _player;
    SList players;
    IPlayer player01;
    IPlayer player02;
    Board _board;
    if (!boardConstructor(&_board)) return 0;

    iPlayerConstructor(&AI, "AI", 1, 0);
    iPlayerConstructor(&_player, player->name, 0, player->points);

    newSList(&players);

    if (!pushSListElement(&players, &AI, sizeof(AI))) return 0;
    if (!pushSListElement(&players, &_player, sizeof(_player))) return 0;

    randomSortSList(&players);

    if (!popSListElement(&players, &player01, sizeof(player01))) return 0;
    if (!popSListElement(&players, &player02, sizeof(player02))) return 0;

    assignForm(&player01, &player02);

    showGameInformation(&player01, &player02);

    printTicTacToe(getArray2D(&_board), &player01, &player02);

    while (getEmptySpaces(&_board) >= 1 && !player01Won && !player02Won) {
        player01Won = makeMove(&player01, &_board, getInternalForm(&player02));
        printTicTacToe(getArray2D(&_board), &player01, &player02);
        if (getEmptySpaces(&_board) < 1 || player01Won) break;

        player02Won = makeMove(&player02, &_board, getInternalForm(&player01));
        printTicTacToe(getArray2D(&_board), &player01, &player02);
        if (player02Won) break;
    }

    if (!player01Won && !player02Won) {
        puts(">TIE");  // TODO. improve output
        addPlayerPoints(player, TIE);
        addPlayerTiedGames(player);
        return 1;
    }
    if (player01Won) {
        printf(">GANO: %s", getNamePlayer(&player01));  // TODO. improve output
        if (strcmp(getNamePlayer(&player01), "AI") == 0) {
            addPlayerPoints(player, DEFEAT);
            addPlayerLostGames(player);
        } else {
            addPlayerPoints(player, VICTORY);
            addPlayerGamesWons(player);
        }
        return 1;
    }
    if (player02Won) {
        printf("\n>GANO PJ 02 %s \n", getNamePlayer(&player02));  // TODO. improve output
        if (strcmp(getNamePlayer(&player01), "AI") == 0) {
            addPlayerPoints(player, DEFEAT);
            addPlayerLostGames(player);

        } else {
            addPlayerPoints(player, VICTORY);
            addPlayerGamesWons(player);
        }
    }

    return 1;
}

// UTILITIES

void showGameInformation(IPlayer *player01, IPlayer *player02) {  // TODO: improve output
    printf("\n> GAME DATA: \n\t Player Name: %s, Form: %c \n", getNamePlayer(player01),
           getExternalForm(player01));
    printf("\t Player Name: %s, Form: %c \n", getNamePlayer(player02), getExternalForm(player02));
    return;
}

int playPlayer(IPlayer *_player, Board *_board, int opponentValue) {
    inputValuePlayer input;
    do {
        getValidatedInput(&input);
    } while (!checkIfThePositionIsFree(getArray2D(_board), &input));

    insertInIntArray2D(getArray2D(_board), getDataInputRaw(&input), getDataInputColumn(&input),
                       getInternalForm(_player));
    updateEmptySpaces(_board);

    return (getEmptySpaces(_board) > 6)
               ? 0
               : checkIfPlayerWon(getArray2D(_board), getInternalForm(_player));
}

unsigned char checkIfPlayerWon(int **_board, int userForm) {
    int valueToWin = userForm * userForm * userForm;

    if (checkTotalRaw(_board, valueToWin) || checkTotalColumn(_board, valueToWin) ||
        checkTotalDiagonal(_board, valueToWin)) {
        return 1;
    }
    return 0;
}
unsigned char checkTotalDiagonal(int **_board, int valueToWin) {
    if (multiplyDiagonalInSquareMatrix(_board, COLUMNS) == valueToWin ||
        multiplySecondaryDiagonalInSquareMatrix(_board, COLUMNS) == valueToWin)
        return 1;
    return 0;
}

unsigned char checkTotalColumn(int **_board, int valueToWin) {
    int iterator;

    for (iterator = 0; iterator < COLUMNS; iterator++) {
        if (multiplyColumn(_board, iterator, RAWS) == valueToWin) {
            return 1;
        }
    }
    return 0;
}

unsigned char checkTotalRaw(int **_board, int valueToWin) {
    int iterator;

    for (iterator = 0; iterator < RAWS; iterator++) {
        if (multiplyRaw(_board, iterator, COLUMNS) == valueToWin) {
            return 1;
        }
    }
    return 0;
}

unsigned char checkIfThePositionIsFree(int **_board, inputValuePlayer *datainput) {
    if (IsThePositionFree(_board, datainput)) {
        puts("\n> Sorry, the position is already taken. Choose another one.\n ");
        return 0;
    }
    return 1;
}

unsigned char IsThePositionFree(int **_board, inputValuePlayer *datainput) {
    return (_board[getDataInputRaw(datainput)][getDataInputColumn(datainput)] != DEFAULT_VALUE) ? 1
                                                                                                : 0;
}

void getValidatedInput(inputValuePlayer *datainput) {
    char _input[4];

    do {
        puts("\n> Enter a coordinate to play. (ex: 0,0) \n WARNING:\n\t(maximum is (2,2)\n");
        fflush(stdin);
        fgets(_input, sizeof(_input), stdin);  // TODO: prevent negative or out range
        fflush(stdin);
    } while (!checkInputFormat(datainput, _input));
    return;
}
unsigned char checkInputFormat(inputValuePlayer *datainput, char *_input) {
    char *pointer = _input;
    int raw, column;

    raw = atoi(pointer);
    if (raw < 0 || raw > 3) {
        puts("\n> No valid Format. Try Again \n");
        return 0;
    }
    pointer++;
    pointer++;
    column = atoi(pointer);
    if (column < 0 || column > 3) {
        puts("\n> No valid Format. Try Again \n");
        return 0;
    }
    datainput->column = column;
    datainput->raw = raw;
    return 1;
}

int playComputer(IPlayer *_AI, Board *_board, int opponentValue) {
    DataAI _AIdata;

    if (getEmptySpaces(_board) > 6) {
        randomMovement(getArray2D(_board), getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }

    DataComputerConstructor(&_AIdata);

    int winThis = getInternalForm(_AI) * getInternalForm(_AI);
    int drawThis = opponentValue * opponentValue;

    checkRaws(getArray2D(_board), &_AIdata, winThis, drawThis);
    checkColumns(getArray2D(_board), &_AIdata, winThis, drawThis);
    checkDiagonals(getArray2D(_board), &_AIdata, winThis, drawThis);

    if (getWinnigMoves(&_AIdata)) {
        winMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        return 1;
    }  // make winner movement
    if (getDrawMoves(&_AIdata)) {
        drawMovement(getArray2D(_board), &_AIdata, getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }

    if (isThereAnyCorner(getArray2D(_board))) {
        playInCorner(getArray2D(_board), getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }
    if (isTheCenterFree(getArray2D(_board))) {
        playInCenter(getArray2D(_board), getInternalForm(_AI));
        updateEmptySpaces(_board);
        return 0;
    }

    randomMovement(getArray2D(_board), getInternalForm(_AI));
    updateEmptySpaces(_board);
    return 0;
}

void playInCenter(int **_board, int valueToInsert) {
    _board[1][1] = valueToInsert;
    return;
}

unsigned char isTheCenterFree(int **_board) { return (_board[1][1] == DEFAULT_VALUE) ? 1 : 0; }

unsigned char isThereAnyCorner(int **_board) {
    if (_board[0][0] == DEFAULT_VALUE) return 1;
    if (_board[0][2] == DEFAULT_VALUE) return 1;
    if (_board[2][0] == DEFAULT_VALUE) return 1;
    if (_board[2][2] == DEFAULT_VALUE) return 1;
    return 0;
}
void playInCorner(int **_board, int valueToInsert) {
    if (_board[0][0] == DEFAULT_VALUE) {
        _board[0][0] = valueToInsert;
        return;
    }
    if (_board[0][2] == DEFAULT_VALUE) {
        _board[0][2] = valueToInsert;
        return;
    }
    if (_board[2][0] == DEFAULT_VALUE) {
        _board[2][0] = valueToInsert;
        return;
    }

    _board[2][2] = valueToInsert;
    return;
}

void printTicTacToe(int **_board, IPlayer *player01, IPlayer *player02) {
    int i, j;

    printf("\n");
    puts("> BOARD:");  // TODO: improve output
    for (i = 0; i < RAWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf(" %c ",
                   (_board[i][j] == DEFAULT_VALUE)
                       ? ' '
                       : ((_board[i][j] == getInternalForm(player01)) ? getExternalForm(player01)
                                                                      : getExternalForm(player02)));
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int CreateInt2DArray(Board *_board, int columns, int raws) {
    int **itertator, **freeiterator;
    int **array = (int **)malloc(raws * sizeof(void *));
    if (!array) return 0;

    for (itertator = array; itertator < array + columns; itertator++) {
        *itertator = (int *)malloc(sizeof(int) * columns);
        if (!*itertator) {
            for (freeiterator = itertator; freeiterator >= array; freeiterator--) {
                free(*freeiterator);
            }
            free(freeiterator);
            return 0;
        }
    }
    _board->array2D = array;
    return 1;
}

int makeMove(IPlayer *_player, Board *_board, int opponentValue) {
    return _player->move(_player, _board, opponentValue);
}

void randomMovement(int **_board, int valueToInsert) {
    int positionRaw, positionColumn;

    srand(time(NULL));

    positionRaw = rand() % RAWS;
    positionColumn = rand() % COLUMNS;

    while (_board[positionRaw][positionColumn] != DEFAULT_VALUE) {
        positionRaw = rand() % RAWS;
        positionColumn = rand() % COLUMNS;
    }

    _board[positionRaw][positionColumn] = valueToInsert;
    return;
}

void drawMovement(int **_board, DataAI *data, int aivalue) {
    if (lastCcDrawRaw(data) != DEF_VALUE_COORDINATES) {
        insertInRaw(_board, lastCcDrawRaw(data), aivalue);
        return;
    }
    if (lastCcDrawColumn(data) != DEF_VALUE_COORDINATES) {
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
    if (lastCWinRaw(data) != DEF_VALUE_COORDINATES) {
        insertInRaw(_board, lastCWinRaw(data), aivalue);
        return;
    }
    if (lastCcWinColumn(data) != DEF_VALUE_COORDINATES) {
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
void initializesArray2D(int **_2dArray, int value, int raws, int columns) {
    int iteratorR, iteratorC;

    for (iteratorR = 0; iteratorR < raws; iteratorR++) {
        for (iteratorC = 0; iteratorC < columns; iteratorC++) {
            _2dArray[iteratorR][iteratorC] = value;
        }
    }
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
    if (isIA) {
        player->_assignedForm = 3;
        player->move = &playComputer;
        return;
    }
    player->_assignedForm = 2;
    player->move = &playPlayer;
    return;
}

int boardConstructor(Board *board) {
    if (!CreateInt2DArray(board, COLUMNS, RAWS)) return 0;
    board->emptySpaces = 9;
    initializesArray2D(board->array2D, DEFAULT_VALUE, RAWS, COLUMNS);
    return 1;
}

// GETTERS
int getEmptySpaces(Board *_board) { return _board->emptySpaces; }
int **getArray2D(Board *board) { return board->array2D; }
int getInternalForm(IPlayer *p) { return p->_assignedForm; }
char getExternalForm(IPlayer *p) { return p->assignedForm; }
char *getNamePlayer(IPlayer *p) { return p->name; }

int lastCcDrawRaw(DataAI *data) { return data->lastCCdraw.raw; }
int lastCcDrawColumn(DataAI *data) { return data->lastCCdraw.column; }
int diagonalDrawValue(DataAI *data) { return data->lastCCdraw.diagonal; }
int lastCWinRaw(DataAI *data) { return data->lastCCwin.raw; }
int lastCcWinColumn(DataAI *data) { return data->lastCCwin.column; }
int diagonalWinValue(DataAI *data) { return data->lastCCwin.diagonal; }
int getWinnigMoves(DataAI *data) { return data->winningMoves; }
int getDrawMoves(DataAI *data) { return data->drawMoves; }
int getDataInputRaw(inputValuePlayer *datainput) { return datainput->raw; }
int getDataInputColumn(inputValuePlayer *datainput) { return datainput->column; }

// SETTERS
void increaseWinningMoves(DataAI *data) { data->winningMoves += 1; }
void increaseDrawMoves(DataAI *data) { data->drawMoves += 1; }
void assignForm(IPlayer *p1, IPlayer *p2) {
    p1->assignedForm = 'X';
    p2->assignedForm = 'O';
}
void saveWinCC(DataAI *data, int *raw, int *column, int *diagonal) {
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

void insertInIntArray2D(int **_array, int raw, int column, int value) {
    _array[raw][column] = value;
}
