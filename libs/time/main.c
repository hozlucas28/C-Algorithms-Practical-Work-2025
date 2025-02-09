
#include "./main.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char concatCurrentTime(char* string) {
    char timeStore[sizeof("YYYY-MM-DD-HH-mm") + 1];

    time_t _time;
    struct tm* _pTime;
    size_t timeLength;

    _time = time(NULL);
    _pTime = localtime(&_time);

    timeLength = strftime(timeStore, sizeof(timeStore), "%Y-%m-%d-%H-%M", _pTime);

    if (timeLength != 16) return 1;

    strcat(string, timeStore);
    return 0;
}
