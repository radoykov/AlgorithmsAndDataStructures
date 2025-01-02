#include<stdio.h>
#include<stdlib.h>
#include"Vector.h"

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void siftUp(Vector* v, int i) {
    if(i <= 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (v->arr[parent] < v->arr[i]) {
        swap(&v->arr[parent], &v->arr[i]);
        siftUp(v, parent);
    }
}

void siftDown(Vector* v, int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int maxIndex;

    if (left >= v->size) {
        return;
    }

    if (right < v->size && v->arr[right] > v->arr[left]) {
        maxIndex = right;
    } else {
        maxIndex = left;
    }

    if (v->arr[i] < v->arr[maxIndex]) {
        swap(&v->arr[i], &v->arr[maxIndex]);
        siftDown(v, maxIndex);
    }
}

int heapPop(Vector* v) {
    if(!v->size) {
        printf("Can't pop empty heap");
        exit(1);
    }
    int val = v->arr[0];
    int a = popVector(v);
    v->arr[0] = a;
    siftDown(v, 0);
    return val;
}

void heapInsert(Vector* v, int val) {
    pushVector(v, val);
    siftUp(v, v->size-1);
}

int main() {
    Vector* v = initVector(8);
    heapInsert(v, 1);
    heapInsert(v, 3);
    heapInsert(v, 8);
    heapInsert(v, 6);
    heapInsert(v, 3);
    heapInsert(v, 7);
    heapInsert(v, 10);
    heapInsert(v, 1);
    
    while (v->size){
        printf("  %d ", heapPop(v));
    }
}