#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
    int *arr;
    int size;
    int capacity;
} Vector;


Vector *initVector(int initialCapacity);

void pushVector(Vector *v, int val);
int popVector(Vector *v);
void printVector(Vector *v);
void releaseVector(Vector *v);

#endif