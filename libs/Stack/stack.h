#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct sNode {
    void *info;
    unsigned sizeInfo;
    struct sNode *next;
} tNode;

typedef tNode *tStack;

void createStack(tStack *ps);  // ps is equal to pointer to stack
int insertIntoStack(tStack *ps, const void *d, unsigned quantityOfBytes);
int grabElementFromStack(tStack *ps, void *d, unsigned quantityOfBytes);
int isTheStackEmpty(const tStack *ps);
int isTheStackFull(const tStack *ps, unsigned quantityOfBytes);
int ViewLastElementOfStack(const tStack *ps, void *d, unsigned quantityOfBytes);
void destroyStack(tStack *ps);

#endif  // STACK_H_INCLUDED