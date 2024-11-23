#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"


SkipList init()
{
    srand(time(NULL));
    SkipList list = {
        .head = createNode(0),
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
    for (int i = 0; i < MAX_LEVEL; i++)
    {
        newNode->next[i] = NULL;
    }
    newNode->val = val;
    return newNode;
}

void insert(SkipList *list, int val) //For given level, each number shows the value of the node which has a pointer at that level.
{
    Node *newNode = createNode(val);

    Node *curr[MAX_LEVEL] = {NULL};
    curr[MAX_LEVEL - 1] = list->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        while (curr[i]->next[i] != NULL && curr[i]->next[i]->val < val)
        {
            curr[i] = curr[i]->next[i];
        }
        if (i > 0)
        {
            curr[i - 1] = curr[i];
        }
    }

    int level = 0;

    do
    {
        newNode->next[level] = curr[level]->next[level];
        curr[level]->next[level] = newNode;
        level++;
    } while (rand() % 2 && level < MAX_LEVEL);
    //} while (level < MAX_LEVEL);
}

void printList(SkipList *list)
{
    Node *curr;
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        curr = list->head;
        printf("Level %d: ", i);
        while (curr)
        {
            printf("%d ", curr->val);
            curr = curr->next[i];
        }
        printf("\n");
    }
}

void release(SkipList *list)
{
    Node *currNode = list->head;
    Node *tempNode;
    while (currNode)
    {
        tempNode = currNode;
        currNode = currNode->next[0];
        free(tempNode);
    }
}