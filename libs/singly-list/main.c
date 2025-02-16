#include "./main.h"

#include <time.h>

#include "../macros.h"

// Private methods
Node* __getNode(SList* _list, const size_t index);

/* ------------------------------- Constructor ------------------------------ */

void newSList(SList* _list) { *_list = NULL; }

/* ------------------------------- Destructor ------------------------------- */

void destroySList(SList* _list) {
    Node* nextNode;

    while (*_list != NULL) {
        nextNode = *_list;
        *_list = nextNode->__next;

        free(nextNode->__data);
        free(nextNode);
    }
}

/* --------------------------------- Getters -------------------------------- */

unsigned char getSListElement(const SList* _list, void* store, const size_t sizeOfStore,
                              const size_t index) {
    size_t length = 0;

    while (*_list != NULL && length != index) {
        _list = &(*_list)->__next;
        length++;
    }

    if (length != index) return 1;

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));

    return 0;
}

size_t getSListLength(SList* _list) {
    size_t length = 0;

    while (*_list != NULL) {
        length++;
        _list = &(*_list)->__next;
    }

    return length;
}

unsigned char getSListHead(const SList* _list, void* store, const size_t sizeOfStore) {
    if (*_list == NULL) return 0;

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));

    return 1;
}

unsigned char isSListEmpty(SList* _list) { return *_list == NULL; }

unsigned char isSListFull(SList* _list, const size_t sizeOfStore) {
    Node* newNode;
    void* newNodeData;

    newNode = malloc(sizeof(Node));
    newNodeData = malloc(sizeOfStore);

    free(newNode);
    free(newNodeData);

    return newNode == NULL || newNodeData == NULL;
}

/* --------------------------------- Methods -------------------------------- */

unsigned char popSListElement(SList* _list, void* store, const size_t sizeOfStore) {
    if (*_list == NULL) return 0;

    while ((*_list)->__next != NULL) _list = &(*_list)->__next;

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));

    free((*_list)->__data);
    free(*_list);
    *_list = NULL;

    return 1;
}

unsigned char pushSListElement(SList* _list, void* data, const size_t sizeOfData) {
    Node* newNode;

    while (*_list != NULL) _list = &(*_list)->__next;

    if ((newNode = malloc(sizeof(Node))) == NULL ||
        (newNode->__data = malloc(sizeOfData)) == NULL) {
        free(newNode);
        return 0;
    }

    memcpy(newNode->__data, data, sizeOfData);
    newNode->__sizeOfData = sizeOfData;
    newNode->__next = NULL;
    *_list = newNode;

    return 1;
}

void mapSList(SList* _list, void (*callback)(void* element)) {
    while (*_list != NULL) {
        callback((*_list)->__data);
        _list = &(*_list)->__next;
    };
}

Node* __getNode(SList* _list, const size_t index) {
    size_t length = 0;

    while (*_list != NULL && length != index) {
        _list = &(*_list)->__next;
        length++;
    }

    return *_list;
}

void randomSortSList(SList* _list) {
    size_t length = 0;

    size_t rndIndex;
    size_t index = 0;

    SList* firstNode = _list;

    Node* rndNode;

    void* oldNodeData;
    size_t oldNodeSizeOfData;

    while (*_list != NULL) {
        length++;
        _list = &(*_list)->__next;
    }

    _list = firstNode;

    if (length == 1) return;

    srand(time(NULL));

    if (length == 2) {
        rndIndex = rand() % length;
        if (rndIndex == index) return;

        rndNode = __getNode(firstNode, rndIndex);

        oldNodeData = (*_list)->__data;
        oldNodeSizeOfData = (*_list)->__sizeOfData;

        (*_list)->__data = rndNode->__data;
        (*_list)->__sizeOfData = rndNode->__sizeOfData;

        rndNode->__data = oldNodeData;
        rndNode->__sizeOfData = oldNodeSizeOfData;

        return;
    }

    while (*_list != NULL) {
        while ((rndIndex = rand() % length) == index);

        rndNode = __getNode(firstNode, rndIndex);

        oldNodeData = (*_list)->__data;
        oldNodeSizeOfData = (*_list)->__sizeOfData;

        (*_list)->__data = rndNode->__data;
        (*_list)->__sizeOfData = rndNode->__sizeOfData;

        rndNode->__data = oldNodeData;
        rndNode->__sizeOfData = oldNodeSizeOfData;

        _list = &(*_list)->__next;
        index++;
    }
}

void selectionSortSList(SList* _list, int (*cmp)(const void* a, const void* b)) {
    void* oldNodeData;
    size_t oldNodeSizeOfData;

    SList* nextNode;
    SList* minorNode;

    if (*_list == NULL) return;

    while ((*_list)->__next != NULL) {
        nextNode = &(*_list)->__next;
        minorNode = _list;

        while (*nextNode != NULL) {
            if (cmp((*minorNode)->__data, (*nextNode)->__data) > 0) minorNode = nextNode;
            nextNode = &(*nextNode)->__next;
        }

        if (*minorNode != *_list) {
            oldNodeData = (*_list)->__data;
            oldNodeSizeOfData = (*_list)->__sizeOfData;

            (*_list)->__data = (*minorNode)->__data;
            (*_list)->__sizeOfData = (*minorNode)->__sizeOfData;

            (*minorNode)->__data = oldNodeData;
            (*minorNode)->__sizeOfData = oldNodeSizeOfData;
        }

        _list = &(*_list)->__next;
    }
}
