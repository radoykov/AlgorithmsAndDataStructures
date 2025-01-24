#include "dynarr.h"
#include <stdlib.h>
#include <stdio.h>

#define ASSERT_MEMORY_ALLOC(PTR)             \
    if (PTR == NULL)                         \
    {                                        \
        printf("Error allocating memory\n"); \
        exit(1);                             \
    }

DynamicArray init(int initialCapacity)
{
    DynamicArray newDynamicArray = {
        .buffer = NULL,
        .size = 0,
        .capacity = initialCapacity};
    if (initialCapacity > 0)
    {
        newDynamicArray.buffer = (void **)calloc(initialCapacity, sizeof(void *));
        ASSERT_MEMORY_ALLOC(newDynamicArray.buffer);
    }

    return newDynamicArray;
}

static void resize(DynamicArray *arr, uint newSize)
{
    if (newSize == 0)
    {
        release(arr);
        return;
    }
    if (newSize > arr->capacity)
    {
        if (arr->capacity == 0)
        {
            arr->capacity = 1;
        }
        while (arr->capacity < newSize)
        {
            arr->capacity *= 2;
        }
        arr->buffer = (void **)realloc(arr->buffer, arr->capacity * sizeof(void *));
        ASSERT_MEMORY_ALLOC(arr->buffer);
    }
    else if (newSize <= arr->capacity / 2)
    {
        arr->capacity = newSize;
        arr->buffer = (void **)realloc(arr->buffer, arr->capacity * sizeof(void *));
        ASSERT_MEMORY_ALLOC(arr->buffer);
    }
    arr->size = newSize;
}

void push(DynamicArray *arr, uint index, void *value)
{
    int newSize = arr->size + 1;
    resize(arr, newSize);
    for (int i = arr->size - 1; i > index; i--)
    {
        arr->buffer[i] = arr->buffer[i - 1];
    }
    arr->buffer[index] = value;
}

void pushFront(DynamicArray *arr, void *value)
{
    push(arr, 0, value);
}

void pushBack(DynamicArray *arr, void *value)
{
    int newSize = arr->size + 1;
    resize(arr, newSize);
    arr->buffer[arr->size - 1] = value;
}

void *getElement(DynamicArray *arr, uint index)
{
    if (index >= arr->size)
    {
        printf("Index out of bounds exception\n");
        exit(1);
    }

    return arr->buffer[index];
}

void setElement(DynamicArray *arr, uint index, void *value)
{
    if (index >= arr->size)
    {
        resize(arr, index + 1);
    }

    arr->buffer[index] = value;
}

void *removeElement(DynamicArray *arr, uint index)
{
    int newSize = arr->size - 1;
    void *result = getElement(arr, index);
    for (int i = index; i < newSize; i++)
    {
        arr->buffer[i] = arr->buffer[i + 1];
    }
    resize(arr, newSize);
    return result;
}

void *popBack(DynamicArray *arr)
{
    return removeElement(arr, arr->size - 1);
}

void *popFront(DynamicArray *arr)
{
    return removeElement(arr, 0);
}

void release(DynamicArray *arr)
{
    free(arr->buffer);
    arr->buffer = NULL;
    arr->capacity = 0;
    arr->size = 0;
}

int contains(DynamicArray *arr, void * value)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->buffer[i] == value)
        {
            return 1;
        }
    }
    return 0;
}