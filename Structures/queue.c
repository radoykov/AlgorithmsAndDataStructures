#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static QNode *createQnode(int val)
{
    QNode *node = (QNode *)malloc(sizeof(QNode));
    node->val = val;
    node->next = NULL;

    return node;
}

Queue *initQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, int val)
{
    QNode *node = createQnode(val);
    if (queue->front == NULL)
    {
        queue->rear = queue->front = node;
        return;
    }

    queue->rear->next = node;
    queue->rear = node;
}

int dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty.\n");
        exit(1);
    }

    QNode *front = queue->front;

    int val = front->val;

    queue->front = front->next;

    free(front);

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    return val;
}

void releaseQueue(Queue *queue)
{
    while (queue->front != NULL)
    {
        dequeue(queue);
    }

    free(queue);
}

void printQueue(Queue *queue)
{
    QNode *it = queue->front;
    printf("\nQueue: ");
    while (it != NULL)
    {
        printf("%d -> ", it->val);
        it = it->next;
    }
    printf("NULL");
}