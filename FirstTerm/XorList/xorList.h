#ifndef XORLIST_H
#define XORLIST_H

typedef struct Node
{
    int value;
    void *pointer;
} Node;

typedef struct XORList
{
    Node *head;
} XORList;

Node *createNode(int val);

XORList init();

void pushFront(XORList *list, int val);
void pushBack(XORList *list, int val);

void printList(XORList *list);

void release(XORList *list);
Node *XOR(Node *a, Node *b);

#endif