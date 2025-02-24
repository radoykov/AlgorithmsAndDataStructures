#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;

    return stack;
}
static StackNode *createStackNode(Node * val)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val = val;
    node->next = NULL;

    return node;
}

void pushStack(Stack *stack, Node * val)
{
    StackNode *node = createStackNode(val);

    node->next = stack->top;
    stack->top = node;
}

Node * popStack(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Stack is empty.\n");
        exit(1);
    }

    Node *val = stack->top->val;
    StackNode *tmp = stack->top;
    stack->top = stack->top->next;
    free(tmp);

    return val;
}

void releaseStack(Stack *stack)
{
    while (stack->top != NULL)
    {
        popStack(stack);
    }

    free(stack);
}

void printStack(Stack *stack)
{
    StackNode *it = stack->top;
    printf("\nStack: ");
    while (it != NULL)
    {
        printf("%d -> ", it->val);
        it = it->next;
    }
    printf("NULL");
}