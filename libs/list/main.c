#include "./main.h"

#include "../macros.h"

Node* __getElementAt(List* _list, const size_t index);

/* ------------------------------- Constructor ------------------------------ */

void newList(List* list) { *list = NULL; }

/* ------------------------------- Destructor ------------------------------- */

void destroyList(List* _list) {
    Node* nextNode;

    while ((*_list) != NULL) {
        nextNode = *_list;
        *(_list) = nextNode->__next;

        free(nextNode->__data);
        free(nextNode);
    }
}

/* --------------------------------- Getters -------------------------------- */

Node* __getElementAt(List* _list, const size_t index) {
    size_t length = 0;

    while ((*_list) != NULL && length != index) {
        _list = &(*_list)->__next;
        length++;
    }

    return *_list;
}

unsigned char getElement(const List* _list, void* store, const size_t sizeOfStore,
                         const size_t index) {
    size_t length = 0;

    while ((*_list) != NULL && length != index) {
        _list = &(*_list)->__next;
        length++;
    }

    if (length != index) return 1;

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));

    return 0;
}

size_t getLength(List* _list) {
    size_t length = 0;

    while ((*_list) != NULL) {
        length++;
        _list = &(*_list)->__next;
    }

    return length;
}

unsigned char getHead(const List* _list, void* store, const size_t sizeOfStore) {
    if ((*_list) == NULL) return 0;

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));

    return 1;
}

unsigned char isListEmpty(List* _list) { return (*_list) == NULL; }

unsigned char isListFull(List* _list, const size_t sizeOfStore) {
    Node* newNode;
    void* newNodeData;

    newNode = malloc(sizeof(Node));
    newNodeData = malloc(sizeOfStore);

    free(newNode);
    free(newNodeData);

    return ((newNode == NULL) || (newNodeData == NULL));
}

/* --------------------------------- Methods -------------------------------- */

unsigned char popElement(List* _list, void* store, const size_t sizeOfStore) {
    if ((*_list) == NULL) {
        return 0;
    }

    while ((*_list)->__next != NULL) {
        _list = &(*_list)->__next;
    }

    memcpy(store, (*_list)->__data, MIN(sizeOfStore, (*_list)->__sizeOfData));
    free((*_list)->__data);
    free(*_list);
    *_list = NULL;

    return 1;
}

unsigned char pushElement(List* _list, void* data, const size_t sizeOfData) {
    Node* newNode;

    while ((*_list) != NULL) {
        _list = &(*_list)->__next;
    };

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

void map(List* _list, void (*callback)(void* element)) {
    while (*_list) {
        callback((*_list)->__data);
        _list = &(*_list)->__next;
    };
}

void randomSort(List* _list) {
    size_t length = 0;
    size_t index = 0;
    size_t rndIndex;

    void* auxPointer;
    size_t elementSize;

    List* head = _list;
    Node* helper;

    while ((*_list) != NULL) {
        length++;
        _list = &(*_list)->__next;
    }

    _list = head;

    if (length == 1) {
        return;
    }
    if (length == 2) {
        rndIndex = (rand() % (length));

        if (rndIndex == index) return;

        helper = __getElementAt(head, rndIndex);
        auxPointer = (*_list)->__data;
        elementSize = (*_list)->__sizeOfData;

        (*_list)->__data = helper->__data;
        (*_list)->__sizeOfData = helper->__sizeOfData;

        helper->__data = auxPointer;
        helper->__sizeOfData = elementSize;
        return;
    }
    while ((*_list) != NULL) {
        while ((rndIndex = (rand() % (length))) == index);
        helper = __getElementAt(head, rndIndex);
        auxPointer = (*_list)->__data;
        elementSize = (*_list)->__sizeOfData;

        (*_list)->__data = helper->__data;
        (*_list)->__sizeOfData = helper->__sizeOfData;

        helper->__data = auxPointer;
        helper->__sizeOfData = elementSize;

        _list = &(*_list)->__next;
        index++;
    }
}

void selectionSort(List* _list, int (*cmp)(const void* a, const void* b)) {
    void* aux;
    unsigned tam;
    List *minor, *iterator;

    if (!(*_list)) return;

    while ((*_list)->__next) {
        iterator = &(*_list)->__next;
        minor = _list;
        while (*iterator) {
            if (cmp((*minor)->__data, (*iterator)->__data) > 0) minor = iterator;
            iterator = &(*iterator)->__next;
        }
        if (*minor != *_list) {
            aux = (*_list)->__data;
            tam = (*_list)->__sizeOfData;

            (*_list)->__data = (*minor)->__data;
            (*_list)->__sizeOfData = (*minor)->__sizeOfData;

            (*minor)->__data = aux;
            (*minor)->__sizeOfData = tam;
        }
        _list = &(*_list)->__next;
    }
}