
#ifndef LIBS_STRUCTS_H_INCLUDED
#define LIBS_STRUCTS_H_INCLUDED

#include <stdlib.h>

typedef struct Node {
    void* __data;
    size_t __sizeOfData;
    struct Node* __next;
} Node;

typedef struct {
    size_t x;
    size_t y;
} Position;

#endif  // LIBS_STRUCTS_H_INCLUDED
