
#include "./utilities.h"

#include <stdio.h>

#include "../../libs/main.h"
#include "../structs.h"
#include "./cJSON/main.h"
#include "./macros.h"

char* parseToJSON(const Configuration* config, SList* players) {
    char* jsonStringified = NULL;

    cJSON* json = NULL;
    cJSON* jsonPlayers = NULL;
    cJSON* jsonPlayer = NULL;

    size_t i;
    const size_t playersLength = getSListLength(players);

    Player player;

    json = cJSON_CreateObject();
    if (json == NULL) goto end;

    if (cJSON_AddStringToObject(json, POST__TEAM_NAME, config->teamName) == NULL) goto end;

    jsonPlayers = cJSON_CreateArray();
    if (jsonPlayers == NULL) goto end;

    cJSON_AddItemToObject(json, POST__PLAYERS, jsonPlayers);

    for (i = 0; i < playersLength; i++) {
        if (getSListElement(players, &player, sizeof(player), i)) break;

        jsonPlayer = cJSON_CreateObject();
        if (jsonPlayer == NULL) goto end;

        cJSON_AddItemToArray(jsonPlayers, jsonPlayer);
        if (cJSON_AddStringToObject(jsonPlayer, POST__PLAYER_NAME, player.name) == NULL) goto end;
        if (cJSON_AddNumberToObject(jsonPlayer, POST__PLAYER_POINTS, player.points) == NULL)
            goto end;
    }

    jsonStringified = cJSON_Print(json);

end:
    cJSON_Delete(json);
    return jsonStringified;
}

size_t writeResponseToTempBFile(void* response, size_t size, size_t nmemb, void* user) {
    const size_t realsize = size * nmemb;

    FILE* file;
    APIPlayer apiPlayer;

    size_t i;
    size_t jsonPlayersLength;

    cJSON* json;
    cJSON* jsonPlayer;
    cJSON* jsonName;
    cJSON* jsonPoints;
    cJSON* jsonLastGamePlayed;

    file = fopen(TEMPORAL_BINARY_FILE, "wb");
    if (file == NULL) return realsize;

    json = cJSON_Parse((char*)response);
    if (json == NULL) goto end;

    jsonPlayersLength = cJSON_GetArraySize(json);

    for (i = 0; i < jsonPlayersLength; i++) {
        jsonPlayer = cJSON_GetArrayItem(json, i);

        jsonName = cJSON_GetObjectItem(jsonPlayer, GET__PLAYER_NAME);
        if (cJSON_IsString(jsonName) && (jsonName->valuestring != NULL)) {
            strcpy(apiPlayer.name, jsonName->valuestring);
        }

        jsonPoints = cJSON_GetObjectItem(jsonPlayer, GET__PLAYER_POINTS);
        if (cJSON_IsNumber(jsonPoints)) {
            apiPlayer.points = jsonPoints->valuedouble;
        }

        jsonLastGamePlayed = cJSON_GetObjectItem(jsonPlayer, GET__LAST_GAME_PLAYED);
        if (cJSON_IsString(jsonLastGamePlayed) && (jsonLastGamePlayed->valuestring != NULL)) {
            strcpy(apiPlayer.lastGamePlayed, jsonLastGamePlayed->valuestring);
        }

        fwrite(&apiPlayer, sizeof(apiPlayer), 1, file);
    }

end:
    fclose(file);
    cJSON_Delete(json);

    return realsize;
}
