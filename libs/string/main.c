
#include "./main.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void trimString(char* string) {
    trimLeftString(string);
    trimRightString(string);
}

void trimLeftString(char* string) {
    size_t i;
    size_t j;
    size_t strLength = strlen(string);

    size_t counter = 0;

    for (i = 0; i < strLength; i++) {
        if (!isspace(*(string + i))) break;
        counter++;
    };

    for (j = 0; j < strLength - counter; j++) {
        *(string + j) = *(string + j + counter);
    };

    *(string + strLength - counter) = '\0';
}

void trimRightString(char* string) {
    size_t i;
    size_t strLength = strlen(string);

    size_t counter = 0;

    for (i = strLength - 1; i > 0; i--) {
        if (!isspace(*(string + i))) break;
        counter++;
    }

    *(string + strLength - counter) = '\0';
}
