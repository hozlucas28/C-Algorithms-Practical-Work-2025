#ifndef LIBS__LIST_H_INCLUDED
#define LIBS__LIST_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#include "../structs.h"

typedef Node* SList; /** Singly linked list */

/* ------------------------------- Constructor ------------------------------ */

/**
 * @brief Initializes a new singly linked list.
 *
 * This function sets the given singly linked list to `NULL`.
 *
 * @param _list Singly linked list structure to be initialized.
 */
void newSList(SList* _list);

/* ------------------------------- Destructor ------------------------------- */

/**
 * @brief Destroys a singly linked list.
 *
 * This function deallocates all the memory used by the nodes in the singly linked list,
 * effectively destroying the list and setting the list pointer to `NULL`.
 *
 * @param _list Singly linked list to be destroyed.
 */
void destroySList(SList* _list);

/* --------------------------------- Getters -------------------------------- */

/**
 * @brief Retrieves a copy of the data at a specific index in the singly linked list.
 *
 * This function copies the data from the node at the specified index in the singly linked list
 * into the provided storage.
 *
 * @param _list Singly linked list.
 * @param store Storage where the data from the specified index will be copied.
 * @param sizeOfStore Size in bytes of the storage.
 * @param index Index of data to be copied.
 *
 * @return 0 if the data was successfully copied, 1 otherwise.
 *
 * @warning Ensure that the storage provided is large enough to hold the data from the specified
 * index.
 */
unsigned char getSListElement(const SList* _list, void* store, const size_t sizeOfStore,
                              const size_t index);

/**
 * @brief Retrieves the length of the singly linked list.
 *
 * @param _list Singly linked list whose length is to be determined.
 *
 * @return Length of the singly linked list.
 */
size_t getSListLength(SList* _list);

/**
 * @brief Retrieves a copy of the top data inside the singly linked list.
 *
 * This function copies the data from the top of the singly linked list into the provided
 * storage.
 *
 * @param _list Singly linked list.
 * @param store Storage where the data from the top will be copied.
 * @param sizeOfStore Size in bytes of the storage.
 *
 * @return 1 if the data was successfully copied, 0 otherwise.
 *
 * @warning Ensure that the storage provided is large enough to hold the top data.
 */
unsigned char getSListHead(const SList* _list, void* store, const size_t sizeOfStore);

/**
 * @brief Checks if the singly linked list is empty.
 *
 * @param _list Singly linked list to be checked.
 *
 * @return 1 if the list is empty, 0 otherwise.
 */
unsigned char isSListEmpty(SList* _list);

/**
 * @brief Checks if the singly linked list can accommodate more data.
 *
 * This function attempts to allocate memory for a new data to determine if the list
 * can accommodate more data. If either allocation fails, the list is considered full.
 *
 * @param _list Singly linked list to be checked.
 * @param sizeOfStore Size in bytes of the data to be stored.
 *
 * @return 1 if the list is full, 0 otherwise.
 *
 * @warning This function temporarily allocates memory to check for fullness and immediately frees
 * it.
 */
unsigned char isSListFull(SList* _list, const size_t sizeOfStore);

/* --------------------------------- Methods -------------------------------- */

/**
 * @brief Removes the last data from the singly linked list and copies its data.
 *
 * This function removes the last data from the singly linked list and copies its data into the
 * provided storage.
 *
 * @param _list Singly linked list from which the last data will be removed.
 * @param store Storage where the data will be copied.
 * @param sizeOfStore Size in bytes of the storage.
 *
 * @return 1 if the data was successfully copied to the store, 0 otherwise.
 *
 * @warning Ensure that the storage provided is large enough to hold data.
 */
unsigned char popSListElement(SList* _list, void* store, const size_t sizeOfStore);

/**
 * @brief Adds a new data to the end of the singly linked list.
 *
 * @param _list Singly linked list where the new data will be added.
 * @param data Data to be stored at the end of the singly linked list.
 * @param sizeOfData Size in bytes of the data to be stored.
 *
 * @return 1 if the data was successfully added, 0 otherwise.
 */
unsigned char pushSListElement(SList* _list, void* data, const size_t sizeOfData);

/**
 * @brief Applies a callback function to each data in the singly linked list.
 *
 * This function iterates through each data in the singly linked list and applies the provided
 * callback function to the data.
 *
 * @param _list Singly linked list whose data will be processed.
 * @param callback Function that will be applied to each data.
 */
void mapSList(SList* _list, void (*callback)(void* element));

/**
 * @brief Randomly shuffles the data of the singly linked list.
 *
 * @param _list Singly linked list to be shuffled.
 */
void randomSortSList(SList* _list);

/**
 * @brief Sorts the singly linked list using the selection sort algorithm.
 *
 * This function sorts the data of the singly linked list in ascending order
 * based on the comparison function provided. The selection sort algorithm repeatedly
 * selects the smallest data from the unsorted portion of the list and swaps it
 * with the first unsorted data.
 *
 * @param _list Singly linked list to be sorted.
 * @param cmp Comparison function.
 */
void selectionSortSList(SList* _list, int (*cmp)(const void* a, const void* b));

#endif  // LIBS__LIST_H_INCLUDED