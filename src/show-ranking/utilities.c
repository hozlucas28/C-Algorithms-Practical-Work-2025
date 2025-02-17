
#include "./utilities.h"

#include "../api/main.h"

int cmpAPIPlayersAsc(const void* playerA, const void* playerB) {
    APIPlayer* _playerA = (APIPlayer*)playerA;
    APIPlayer* _playerB = (APIPlayer*)playerB;
    return _playerB->points - _playerA->points;
}
