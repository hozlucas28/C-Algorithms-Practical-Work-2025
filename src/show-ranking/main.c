
#include "./main.h"

#include <stdio.h>
#include <string.h>

#include "../../libs/main.h"
#include "../api/main.h"
#include "../structs.h"

unsigned char __concatEndpoint(const char* base, const char* endpoint, char* store);

unsigned char showRanking(const Configuration* config) {
    unsigned char error = 1;
    char endpoint[MAXIMUM_API_URL_LENGTH];

    List players;
    newList(&players);

    error = __concatEndpoint(config->apiURL, config->teamName, endpoint);
    if (!error) {
        printf("> Error! An error occurred on create endpoint.\n\n");
        return 0;
    }

    printf("\n\n> %s\n\n", endpoint);

    error = getAPI(endpoint, &players);
    if (!error) {
        printf("> Error! An error occurred on get players.\n\n");
        return 0;
    }

    // TODO: sort by points and print ranking

    return 1;
}

unsigned char __concatEndpoint(const char* base, const char* endpoint, char* store) {
    strcpy(store, base);
    strcat(store, "/");
    strcat(store, endpoint);

    return 1;
}
