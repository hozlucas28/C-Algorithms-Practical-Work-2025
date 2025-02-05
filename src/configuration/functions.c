
#include <stdio.h>
#include <string.h>

#include "./macros.h"
#include "./structs.h"

unsigned char getConfiguration(Configuration* config, const char* path) {
    char line[CONFIGURATION_LINE_LENGTH];

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
    strcpy(config->apiURL, fieldStart);

    fieldStart = fieldEnd + 1;
    fieldEnd = strchr(fieldStart, ' ');
    if (fieldEnd == NULL) return 1;

    fieldStart = fieldEnd + 1;
    lineBreak = strrchr(fieldStart, '\n');
    if (lineBreak != NULL) {
        *lineBreak = '\0';
    };

    strcpy(config->teamName, fieldStart);

    if (fgets(line, sizeof(line), file) == NULL) return 1;

    sscanf(line, "%d", &config->gamesPerPlayer);

    return 0;
}
