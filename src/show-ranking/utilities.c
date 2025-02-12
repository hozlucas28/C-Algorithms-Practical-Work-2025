
#include "./utilities.h"

#include "../structs.h"

int cmpPlayers(const void* playerA, const void* playerB) {
    APIPlayer* _playerA = (APIPlayer*)playerA;
    APIPlayer* _playerB = (APIPlayer*)playerB;
    return _playerB->points - _playerA->points;
}