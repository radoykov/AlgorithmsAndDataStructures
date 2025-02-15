#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}
static StackNode *createStackNode(void *val)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val = val;
    node->next = NULL;

    return node;
}

void pushStack(Stack *stack, void *val)
{
    StackNode *node = createStackNode(val);

    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

void *popStack(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Stack is empty.\n");
        exit(1);
    }

    void *val = stack->top->val;
    StackNode *tmp = stack->top;
    stack->top = stack->top->next;
    free(tmp);
    stack->size--;
    return val;
}

void releaseStack(Stack *stack)
{
    while (stack->top != NULL)
    {
        free(popStack(stack));
    }
    stack->size = 0;
    free(stack);
}