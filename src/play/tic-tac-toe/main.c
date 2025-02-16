#include "./main.h"

#include <stdio.h>
#include <time.h>

#include "../../../libs/main.h"
#include "../../configuration/main.h"
#include "../../player/main.h"
#include "../../utilities.h"
#include "./main.h"
#include "./utilities.h"

unsigned char playGame(Player* player) {
    Player ai;
    Player _player;

    SList players;

    Player player01;
    Player player02;

    unsigned char player01Won = 0;
    unsigned char player02Won = 0;

    Board* board = newBoard(BOARD_ROWS, BOARD_COLS, BOARD_DEFAULT_VALUE);
    if (board == NULL) return 0;

    newPlayer(&_player, getPlayerName(player));

    setPlayerAssignedFormValue(&_player, PLAYER_ASSIGNED_FORM_VALUE);
    setPlayerPlayMethod(&_player, &_playPlayer);

    newPlayer(&ai, "AI");

    setPlayerAI(&ai, 1);
    setPlayerAssignedFormValue(&ai, AI_ASSIGNED_FORM_VALUE);
    setPlayerPlayMethod(&ai, &_playAI);

    newSList(&players);

    if (!pushSListElement(&players, &ai, sizeof(ai))) {
        destroyBoard(board);
        return 0;
    };

    if (!pushSListElement(&players, &_player, sizeof(_player))) {
        destroyBoard(board);
        return 0;
    };

    randomSortSList(&players);

    if (!popSListElement(&players, &player01, sizeof(player01))) {
        destroyBoard(board);
        return 0;
    };

    if (!popSListElement(&players, &player02, sizeof(player02))) {
        destroyBoard(board);
        return 0;
    };

    setPlayerAssignedForm(&player01, 'X');
    setPlayerAssignedForm(&player02, 'O');

    printf("> %s your form is \"%c\", and \"%c\" is for %s.\n\n", getPlayerName(&player01),
           getPlayerAssignedForm(&player01), getPlayerAssignedForm(&player02),
           getPlayerName(&player02));

    while (getBoardFreeCells(board) > 0 && !player01Won && !player02Won) {
        player01Won = playerPlay(&player01, board, getPlayerAssignedFormValue(&player02));
        showBoard(board, &player01, &player02);

        if (getBoardFreeCells(board) < 1 || player01Won) break;

        player02Won = playerPlay(&player02, board, getPlayerAssignedFormValue(&player01));
        showBoard(board, &player01, &player02);
    }

    if (player01Won) {
        printf("> %s won!\n\n", getPlayerName(&player01));

        appendPlayerPoints(&player01, POINTS_FOR_VICTORY);
        appendPlayerPoints(&player02, POINTS_FOR_LOSS);

        appendPlayerGamesWon(&player01, 1);
        appendPlayerLostGames(&player02, 1);

        goto end;
    }

    if (player02Won) {
        printf("> %s won!\n\n", getPlayerName(&player02));

        appendPlayerPoints(&player02, POINTS_FOR_VICTORY);
        appendPlayerPoints(&player01, POINTS_FOR_LOSS);

        appendPlayerGamesWon(&player02, 1);
        appendPlayerLostGames(&player01, 1);

        goto end;
    }

    puts("> It's a tie!\n");

    appendPlayerPoints(&player01, POINTS_FOR_TIE);
    appendPlayerPoints(&player02, POINTS_FOR_TIE);

    appendPlayerTiedGames(&player01, 1);
    appendPlayerTiedGames(&player02, 1);

end:
    destroyBoard(board);

    if (isPlayerAI(&player02)) {
        appendPlayerGamesWon(player, getPlayerGamesWon(&player01));
        appendPlayerLostGames(player, getPlayerLostGames(&player01));
        appendPlayerTiedGames(player, getPlayerTiedGames(&player01));
        appendPlayerPoints(player, getPlayerPoints(&player01));
    } else {
        appendPlayerGamesWon(player, getPlayerGamesWon(&player02));
        appendPlayerLostGames(player, getPlayerLostGames(&player02));
        appendPlayerTiedGames(player, getPlayerTiedGames(&player02));
        appendPlayerPoints(player, getPlayerPoints(&player02));
    };

    return 1;
}
