#ifndef SRC__API_H_INCLUDED
#define SRC__API_H_INCLUDED

#include "../../libs/main.h"
#include "../configuration/main.h"
#include "./macros.h"
#include "./utilities.h"

unsigned char getAPI(const char* endpoint, List* players);

unsigned char postAPI(const Configuration* config, List* players);

unsigned char createLocalRecord(const Configuration* config, List* players);

#endif  // SRC__API_H_INCLUDED
