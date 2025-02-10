#ifndef LIBS__LIST_H_INCLUDED
#define LIBS__LIST_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#include "../structs.h"

/* ---------- List ---------- */

typedef Node* List;

// Constructor
void newList(List* list);

// Destroyer
void destroyList(List* _list);

// Getters
unsigned char getHead(const List* _list, void* store, const size_t sizeOfStore);

unsigned char getElement(const List* _list, void* store, const size_t sizeOfStore,
                         const size_t index);

unsigned char isListEmpty(List* _list);

unsigned char isListFull(List* _list, const size_t sizeOfStore);

size_t getLength(List* _list);

// Methods
unsigned char pushElement(List* _list, void* data, const size_t sizeOfData);

unsigned char popElement(List* _list, void* store, const size_t sizeOfStore);

void randomSort(List* _list);

#endif  // LIBS__LIST_H_INCLUDED