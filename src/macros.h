#ifndef SRC_MACROS_H_INCLUDED
#define SRC_MACROS_H_INCLUDED

/* --------------------------------- Common --------------------------------- */

#define DEVELOPMENT_TEAM "SQUASH"

#define TEAM_NAME_LENGTH 32

#define CONFIGURATION_PATH "./statics/configuration.txt"

#define LOCAL_FILE_PATH "./statics/local-storage/informe-juego_"

#define LOCAL_FILE_PATH_LENGTH \
    (sizeof(LOCAL_FILE_PATH) + sizeof("YYYY-MM-DD-HH-mm") + sizeof(".txt") + 1)

/* --------------------------------- Player --------------------------------- */

#define PLAYER_NAME_LENGTH 64

#define PLAYER_LAST_GAME_PLAYED_LENGTH 32

#endif  // SRC_MACROS_H_INCLUDED
