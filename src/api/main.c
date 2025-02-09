
#include "../../libs/main.h"

#include <stdio.h>
#include <string.h>

#include "../structs.h"
#include "./main.h"

unsigned char postAPI(const Configuration* config, List* list) {
    return 0;
    // TODO
}

unsigned char createLocalRecord(const Configuration* config, List* players, char* localFilePath) {
    unsigned char error;

    FILE* file;

    // Chars per column
    const int indexCol = 2;
    const int nameCol = PLAYER_NAME_LENGTH;
    const int pointsCol = 6;
    const int columns = 3;
    const int separatorsBetweenCols = columns - 1;

    const int lineLength = (indexCol + nameCol + pointsCol) + (columns * 2) + separatorsBetweenCols;

    int i;
    Player player;
    size_t playersLength;

    error = concatCurrentTime(localFilePath);
    if (error) return 1;

    strcat(localFilePath, ".txt");

    file = fopen(localFilePath, "wt");
    if (file == NULL) return 1;

    // Header - Team name
    fprintf(file, "> Team name: %s.\n\n", config->teamName);

    // Table - Start line
    fputc('+', file);
    for (i = 0; i < lineLength; i++) fputc('-', file);
    fprintf(file, "+\n");

    // Table - Titles
    fprintf(file, "| N° | %-*s | Points |\n", nameCol, "Player name");

    // Table - Separator line
    fputc('|', file);
    for (i = 0; i < lineLength; i++) {
        if (i == indexCol + 2 || i == indexCol + 2 + 1 + nameCol + 2) {
            fputc('|', file);
            continue;
        };

        fputc('-', file);
    };
    fprintf(file, "|\n");

    playersLength = getLength(players);

    // Table - Content
    for (i = 0; i < playersLength; i++) {
        error = getElement(players, &player, sizeof(player), i);
        if (error) break;

        fprintf(file, "| %0*d | %-*s | %0*d |\n", indexCol, i + 1, nameCol, player.name, pointsCol,
                player.points);
    };

    // Table - End line
    fputc('+', file);
    for (i = 0; i < lineLength; i++) fputc('-', file);
    fputc('+', file);

    fclose(file);

    return 0;
}
