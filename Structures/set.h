#ifndef SET_H
#define SET_H

typedef struct Set
{
    int size;
    int capacity;
    int *data;
} Set;

Set *initSet();

int setContains(Set *set, int val);

void setAdd(Set *set, int val);

void printSet(Set *set);

void releaseSet(Set *set);

#endif