
#ifndef LIBS_STRUCTS_H_INCLUDED
#define LIBS_STRUCTS_H_INCLUDED

#include <stdlib.h>

/**
 * @struct Node
 *
 * @brief Node allocated in the HEAP memory.
 */
typedef struct Node {
    void* __data;        /** Pointer to the data stored. */
    size_t __sizeOfData; /** Size in bytes of the stored data. */
    struct Node* __next; /** Pointer to the next linked node. */
} Node;

// TODO: create doxygen documentation
typedef struct {
    size_t x;
    size_t y;
} Position;

#endif  // LIBS_STRUCTS_H_INCLUDED
