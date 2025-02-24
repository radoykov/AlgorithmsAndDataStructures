#ifndef STACK_H
#define STACK_H

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct StackNode
{
    Node *val;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

Stack *initStack();
static StackNode *createStackNode(Node *val);

void pushStack(Stack *stack, Node *val);
Node *popStack(Stack *stack);

void releaseStack(Stack *stack);
void printStack(Stack *stack);

#endif