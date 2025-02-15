#ifndef SRC__API_H_INCLUDED
#define SRC__API_H_INCLUDED

#include "../../libs/main.h"
#include "../configuration/main.h"
#include "./macros.h"
#include "./utilities.h"

unsigned char getAPI(const char* endpoint, SList* players);

unsigned char postAPI(const Configuration* config, SList* players);

unsigned char createLocalRecord(Configuration* config, SList* players);

#endif  // SRC__API_H_INCLUDED
