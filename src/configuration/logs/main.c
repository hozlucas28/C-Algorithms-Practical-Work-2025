#include "./main.h"

#include <stdio.h>

void reprConfiguration(Configuration* config) {
    if (config == NULL) {
        printf("Configuration 0x%p (NULL);", (void*)&config);
        return;
    };

    printf("Configuration 0x%p {\n", (void*)&config);
    printf("  char apiURL[%d] = \"%s\",\n", API_URL_LENGTH, config->apiURL);
    printf("  char localRecordPath[%d] = \"%s\",\n", (int)LOCAL_RECORD_PATH_LENGTH, config->teamName);
    printf("  char teamName[%d] = \"%s\",\n", (int)TEAM_NAME_LENGTH, config->teamName);
    printf("  int gamesPerPlayer = %d,\n", config->gamesPerPlayer);
    printf("};");
}
