#ifndef STACK_H
#define STACK_H


typedef struct StackNode
{
    void *val;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
    int size;
} Stack;


Stack *initStack();

static StackNode *createStackNode(void *val);
void pushStack(Stack *stack, void *val);
void *popStack(Stack *stack);

void releaseStack(Stack *stack);
#endif