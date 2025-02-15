#ifndef SRC__API_UTILITIES_H_INCLUDED
#define SRC__API_UTILITIES_H_INCLUDED

#include "../../libs/main.h"
#include "../configuration/main.h"

char* parseToJSON(const Configuration* config, SList* players);

size_t writeResponseToTempBFile(void* response, size_t size, size_t nmemb, void* user);

#endif  // SRC__API_UTILITIES_H_INCLUDED
