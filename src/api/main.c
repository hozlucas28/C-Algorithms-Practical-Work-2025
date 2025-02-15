
#include "../../libs/main.h"

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#include "../structs.h"
#include "./cJSON/main.h"
#include "./main.h"
#include "./utilities.h"

unsigned char getAPI(const char* endpoint, List* players) {
    unsigned char error = 1;

    CURL* curl;
    CURLcode response;

    APIPlayer apiPlayer;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_URL, endpoint);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeResponseToTempBFile);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) error = 0;

        curl_easy_cleanup(curl);
    };

    curl_global_cleanup();

    FILE* file = fopen(TEMPORAL_BINARY_FILE, "rb");
    if (file == NULL) return 1;

    while (fread(&apiPlayer, sizeof(apiPlayer), 1, file) &&
           pushElement(players, &apiPlayer, sizeof(apiPlayer)));

    fclose(file);

    remove(TEMPORAL_BINARY_FILE);

    return error;
}

unsigned char postAPI(const Configuration* config, List* players) {
    char* json = NULL;
    unsigned char error = 0;

    CURL* curl;
    struct curl_slist* headers = NULL;
    CURLcode response;

    json = parseToJSON(config, players);
    if (json == NULL) return 1;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_URL, config->apiURL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) error = 1;

        curl_easy_cleanup(curl);
    };

    curl_global_cleanup();

    free(json);

    return error;
}

unsigned char createLocalRecord(const Configuration* config, List* players) {
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

    error = concatCurrentTime(config->localRecordPath);
    if (error) return 1;

    strcat(config->localRecordPath, ".txt");

    file = fopen(config->localRecordPath, "wt");
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
