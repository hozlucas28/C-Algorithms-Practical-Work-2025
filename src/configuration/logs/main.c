#include "./main.h"

#include <stdio.h>

void reprConfiguration(Configuration* config) {
    if (config == NULL) {
        printf("Configuration 0x%p (NULL);", (void*)&config);
        return;
    };

    printf("Configuration 0x%p {\n", (void*)&config);
    printf("  char apiURL[MAXIMUM_API_URL_LENGTH] = \"%s\",\n", config->apiURL);
    printf("  char teamName[TEAM_NAME_LENGTH] = \"%s\",\n", config->teamName);
    printf("  int gamesPerPlayer = %d,\n", config->gamesPerPlayer);
    printf("};");
}
