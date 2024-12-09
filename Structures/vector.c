#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

Vector *initVector(int initialCapacity)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->arr = (int *)malloc(initialCapacity * sizeof(int));
    v->size = 0;
    v->capacity = initialCapacity;

    return v;
}

void pushVector(Vector *v, int val)
{

    if (v->size > v->capacity)
    {
        v->capacity = v->capacity * 2;

        int *tmp = (int *)realloc(v->arr, sizeof(int) * v->capacity);
        if (tmp == NULL)
        {
            exit(0);
        }
        v->arr = tmp;
    }

    v->size++;
    v->arr[v->size - 1] = val;
}

int popVector(Vector *v)
{
    if (v->size == 0)
    {
        printf("cannot pop from empty array");
        exit(0);
    }
    if (v->size  <= v->capacity /2)
    {
        v->capacity = v->capacity / 2;

        int *tmp = (int *)realloc(v->arr, sizeof(int) * v->capacity);
        if (tmp == NULL)
        {
            exit(0);
        }
        v->arr = tmp;
    }

    int tmp = v->arr[v->size - 1];
    v->size--;

    return tmp;
}

void printVector(Vector *v)
{
    printf("\nVector:");
    for (int i = 0; i < v->size; i++)
    {
        printf("%d -> ", v->arr[i]);
    }
    printf("NULL");
}

void releaseVector(Vector *v)
{
    free(v->arr);
    free(v);
}