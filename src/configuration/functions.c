
#include <stdio.h>
#include <string.h>

#include "./macros.h"
#include "./structs.h"

unsigned char getConfiguration(Configuration* config, const char* path) {
    size_t fieldsRead = 0;
    char line[CONFIGURATION_LINE_LENGTH];

    char apiURL[API_URL_LENGTH];
    char localRecordPath[LOCAL_RECORD_PATH_LENGTH];
    char teamName[TEAM_NAME_LENGTH];
    int gamesPerPlayer;

    char* fieldStart;
    char* fieldEnd;

    char* lineBreak;

    FILE* file = fopen(path, "rt");
    if (file == NULL) return 1;

    if (fgets(line, sizeof(line), file) == NULL) return 1;

    fieldStart = line;
    fieldEnd = strchr(fieldStart, ' ');
    if (fieldEnd == NULL) return 1;

    *fieldEnd = '\0';
    if (strlen(fieldStart) == 0) return 1;
    strcpy(apiURL, fieldStart);

    fieldStart = fieldEnd + 1;
    fieldEnd = strchr(fieldStart, ' ');
    if (fieldEnd == NULL) return 1;

    fieldStart = fieldEnd + 1;
    lineBreak = strrchr(fieldStart, '\n');
    if (lineBreak != NULL) *lineBreak = '\0';

    strcpy(teamName, fieldStart);

    if (fgets(line, sizeof(line), file) == NULL) return 1;

    fieldsRead = sscanf(line, "%d", &gamesPerPlayer);
    if (fieldsRead != 1) return 1;

    strcpy(localRecordPath, LOCAL_RECORD_PATH);

    strcpy(config->apiURL, apiURL);
    strcpy(config->teamName, teamName);
    config->gamesPerPlayer = gamesPerPlayer;
    strcpy(config->localRecordPath, LOCAL_RECORD_PATH);

    return 0;
}
