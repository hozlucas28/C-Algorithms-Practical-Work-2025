#ifndef LIBS__TIME_H_INCLUDED
#define LIBS__TIME_H_INCLUDED

/**
 * @brief Concatenates the current time to the given string.
 *
 * This function retrieves the current system time and appends it to the provided string.
 * The concatenated time format is YYYY-MM-DD-HH-mm.
 *
 * @param string String on which the current time will be concatenated.
 *
 * @return 0 if the operation is successful, 1 otherwise.
 *
 * @warning Ensure that the provided string has sufficient space to hold the concatenated time.
 */
unsigned char concatCurrentTime(char* string);

#endif  // LIBS__TIME_H_INCLUDED