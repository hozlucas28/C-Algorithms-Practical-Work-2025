#include "../libs/main.h"

#include <stdio.h>
#include <stdlib.h>

#include "./utilities.h"

int main(const int argsLength, char* args[]) {
    // TODO: delete function calls
    greetFromSrc();
    printf("\n");
    greetFromLibs();

    return 0;
}
