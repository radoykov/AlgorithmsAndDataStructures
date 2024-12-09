#include <stdio.h>
#include "set.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"

int main() 
{
    //using set
    Set * set = initSet();

    setAdd(set, 1);
    setAdd(set, 5);
    setAdd(set, 7);

    printf("\n%d", setContains(set, 5));
    printf("\n%d", setContains(set, 10));

    printSet(set);
    releaseSet(set);

    //using queue
    Queue * queue = initQueue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 5);
    enqueue(queue, 7);

    printQueue(queue);


    dequeue(queue);
    dequeue(queue);

    printQueue(queue);

    releaseQueue(queue);

    //using stack

    Stack * stack = initStack();

    pushStack(stack, 1);
    pushStack(stack, 2);
    pushStack(stack, 3);

    printStack(stack);

    popStack(stack);
    popStack(stack);

    printStack(stack);
    releaseStack(stack);

    //using vector

    
    Vector * vector = initVector(1);

    pushVector(vector, 1);
    pushVector(vector, 2);
    pushVector(vector, 3);

    printVector(vector);

    popVector(vector);
    popVector(vector);

    printVector(vector);
    releaseVector(vector);

    return 0;
}