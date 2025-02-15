#ifndef SRC__API_MACROS_H_INCLUDED
#define SRC__API_MACROS_H_INCLUDED

#include "../player/macros.h"

#define TEMPORAL_BINARY_FILE "./json.temp.dat"

/* ------------------------------- Structures ------------------------------- */

#define API_PLAYER_NAME_LENGTH PLAYER_NAME_LENGTH

#define API_PLAYER_LAST_GAME_PLAYED_LENGTH 19

/* ---------------------------- JSON Fields - GET --------------------------- */

#define GET__PLAYER_NAME "nombreJugador"

#define GET__PLAYER_POINTS "puntaje"

#define GET__LAST_GAME_PLAYED "ultimaPartidaJugada"

/* --------------------------- JSON Fields - POST --------------------------- */

#define POST__TEAM_NAME "CodigoGrupo"

#define POST__PLAYERS "Jugadores"

#define POST__PLAYER_NAME "nombre"

#define POST__PLAYER_POINTS "puntos"

#endif  // SRC__API_MACROS_H_INCLUDED
