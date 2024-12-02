#include <stdio.h>
#include <stdlib.h>
#include "xorList.h"

XORList init()
{
  XORList list = {
      .head = NULL,
  };
  return list;
}

Node *createNode(int val)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL)
  {
    printf("Couldn't allocate for new node\n");
    exit(1);
  }
  newNode->pointer = NULL;
  newNode->value = val;
  return newNode;
}

void pushFront(XORList *list, int val)
{

  Node *newNode = createNode(val);

  Node *first = list->head;
  if (first == NULL)
  {
    list->head = newNode;
    return;
  }
  Node *second = XOR(first->pointer, NULL);

  first->pointer = XOR(newNode, second);
  newNode->pointer = XOR(NULL, first);

  list->head = newNode;
}

void pushBack(XORList *list, int val)
{
  Node *newNode = createNode(val);

  Node *first = list->head;
  Node *last = NULL;

  if (first == NULL)
  {
    list->head = newNode;
    return;
  }

  while (first != NULL)
  {
    void *temp = last;

    last = first;
    first = XOR(first->pointer, temp);
  }
  Node *secondLast = XOR(last->pointer, NULL);
  last->pointer = XOR(secondLast, newNode);

  newNode->pointer = XOR(last, NULL);
}

void printList(XORList *list)
{
  Node *prev = NULL;
  Node *curr = list->head;

  Node *temp = NULL;
  while (curr != NULL)
  {
    temp = prev;
    printf("%d, ", curr->value);
    prev = curr;
    curr = XOR(curr->pointer, temp);
  }
  printf("\n");
}

void release(XORList *list)
{
  Node *prev = NULL;
  Node *curr = list->head;
  Node *next;

  while (curr != NULL)
  {
    next = XOR(curr->pointer, prev);
    prev = curr;
    curr = next;
    free(prev);
  }
}

Node *XOR(Node *a, Node *b)
{
  return (Node *)((uintptr_t)(a) ^ (uintptr_t)(b));
}