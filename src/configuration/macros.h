#ifndef SRC__CONFIG_MACROS_H_INCLUDED
#define SRC__CONFIG_MACROS_H_INCLUDED

#define CONFIGURATION_PATH "./statics/configuration.txt"

#define API_URL_LENGTH 256

#define LOCAL_RECORD_PATH "./statics/local-storage/informe-juego_"

#define LOCAL_RECORD_PATH_LENGTH \
    (sizeof(LOCAL_RECORD_PATH) + sizeof("YYYY-MM-DD-HH-mm") + sizeof(".txt") + 1)

#define TEAM_NAME_LENGTH 32

#define CONFIGURATION_LINE_LENGTH 256

#endif  // SRC__CONFIG_MACROS_H_INCLUDED