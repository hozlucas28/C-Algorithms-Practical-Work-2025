#ifndef LIBS__STRING_H_INCLUDED
#define LIBS__STRING_H_INCLUDED

/**
 * @brief Trims leading and trailing whitespace characters from a string.
 *
 * This function trims leading and trailing whitespace characters from a string
 * by modifying the string in-place.
 *
 * @param string The string to trim.
 *
 * @warning This function assumes that the input string is null-terminated.
 */
void trimString(char* string);

/**
 * @brief Trims leading whitespace characters from a string.
 *
 * This function trims leading whitespace characters from a string by modifying
 * the string in-place.
 *
 * @param string The string to trim.
 *
 * @warning This function assumes that the input string is null-terminated.
 */
void trimLeftString(char* string);

/**
 * @brief Trims trailing whitespace characters from a string.
 *
 * This function trims trailing whitespace characters from a string by modifying
 * the string in-place.
 *
 * @param string The string to trim.
 *
 * @warning This function assumes that the input string is null-terminated.
 */
void trimRightString(char* string);

#endif  // LIBS__STRING_H_INCLUDED