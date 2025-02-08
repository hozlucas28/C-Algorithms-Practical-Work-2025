#ifndef SRC__API_H_INCLUDED
#define SRC__API_H_INCLUDED

#include "../../libs/main.h"
#include "../configuration/main.h"

unsigned char postAPI(const Configuration* config, List* list);

unsigned char createLocalFile(List* list, const char* localFilePath);

#endif  // SRC__API_H_INCLUDED