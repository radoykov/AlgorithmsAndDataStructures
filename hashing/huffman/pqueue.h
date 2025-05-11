#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdio.h>
#define MAX_PQ_NODES 1000
#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct PQNode
{
    float key;
    void *data;
} PQNode;

typedef struct PQueue
{
    PQNode *arr[MAX_PQ_NODES];
    int size;
} PQueue;

PQueue *initPQ();
PQNode *initPQNode(void *data, float key);
void swap(PQNode **a, PQNode **b);
void siftDown(PQueue *pq, int i);
PQNode *deleteMin(PQueue *pq);
void pqInsert(PQueue *pq, void *data, float key);
void freePQ(PQueue *pq);

#endif