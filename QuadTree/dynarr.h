#ifndef DYN_ARR_H
#define DYN_ARR_H

typedef unsigned int uint;

typedef struct {
  void ** buffer;
  uint size;
  uint capacity;
} DynamicArray;

DynamicArray init(int initialCapacity);

void push(DynamicArray *arr, uint index, void * value);
void pushFront(DynamicArray *arr, void * value);
void pushBack(DynamicArray *arr, void * value);

void * getElement(DynamicArray *arr, uint index);
void setElement(DynamicArray *arr, uint index, void * value);

void * removeElement(DynamicArray * arr, uint index);
void * popBack(DynamicArray *arr);
void * popFront(DynamicArray *arr);

int contains(DynamicArray *arr, void * value);

void release(DynamicArray * arr);
#endif