#ifndef STACK_H
#define STACK_H

typedef struct StackNode
{
    int val;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

Stack *initStack();
static StackNode *createStackNode(int val);


void pushStack(Stack *stack, int val);
int popStack(Stack *stack);

void releaseStack(Stack *stack);
void printStack(Stack *stack);

#endif