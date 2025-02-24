#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// task 1

Node *createNode(int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *bstInsert(Node *node, int val)
{
    if (!node)
    {
        return createNode(val);
    }
    if (val < node->val)
    {
        node->left = bstInsert(node->left, val);
    }
    else if (val > node->val)
    {
        node->right = bstInsert(node->right, val);
    }
    return node;
}

// task 2
// Валидно решение на задачата, но ще доведе до проблеми, ако използваме t2 след нея
Node *mergeTwo(Node *t1, Node *t2)
{
    if (!t1)
    {
        return t2;
    }
    if (!t2)
    {
        return t1;
    }

    t1->val += t2->val;
    t1->left = mergeTwo(t1->left, t2->left);
    t1->right = mergeTwo(t1->right, t2->right);
    return t1;
}

// Примерно решение чрез създаване на ново дърво
Node *mergeTwoIntoNew(Node *t1, Node *t2)
{
    if (!t1 && !t2)
        return NULL;

    int val1 = t1 ? t1->val : 0;
    int val2 = t2 ? t2->val : 0;

    Node *t = createNode(val1 + val2);
    t->left = mergeTwoIntoNew(t1 ? t1->left : NULL, t2 ? t2->left : NULL);
    t->right = mergeTwoIntoNew(t1 ? t1->right : NULL, t2 ? t2->right : NULL);

    return t;
}

void printPreorder(Node *node)
{
    if (!node)
    {
        return;
    }

    printf("%d ", node->val);
    printPreorder(node->left);
    printPreorder(node->right);
}

// task 3
void zigzagTraverse(Node *node)
{
    if (!node)
    {
        return;
    }
    Stack *currLevel = initStack();
    Stack *nextLevel = initStack();
    pushStack(currLevel, node);
    int leftToRight = 1;

    while (currLevel->top)
    {
        Node *curr = popStack(currLevel);
        printf("%d ", curr->val);

        if (leftToRight)
        {
            if (curr->left)
            {
                pushStack(nextLevel, curr->left);
            }
            if (curr->right)
            {
                pushStack(nextLevel, curr->right);
            }
        }
        else
        {
            if (curr->right)
            {
                pushStack(nextLevel, curr->right);
            }
            if (curr->left)
            {
                pushStack(nextLevel, curr->left);
            }
        }

        if (!currLevel->top)
        {
            Stack *tmp = nextLevel;
            nextLevel = currLevel;
            currLevel = tmp;
            leftToRight = !leftToRight;
        }
    }
    releaseStack(currLevel);
    releaseStack(nextLevel);
}


int main()
{
    Node *tree = createNode(10);
    bstInsert(tree, 20);
    bstInsert(tree, 5);
    bstInsert(tree, 1);
    bstInsert(tree, 8);
    bstInsert(tree, 2);
    bstInsert(tree, 15);
    bstInsert(tree, 25);
    bstInsert(tree, 22);

    Node *t1 = createNode(1);
    t1->left = createNode(3);
    t1->right = createNode(2);
    t1->left->left = createNode(5);

    Node *t2 = createNode(2);
    t2->left = createNode(1);
    t2->right = createNode(3);
    t2->left->right = createNode(4);
    t2->right->right = createNode(7);

    Node *t3 = mergeTwoIntoNew(t1, t2);

    mergeTwo(t1, t2);

    printPreorder(t1);
    printf("\n");

    printPreorder(t3);
    printf("\n");

    zigzagTraverse(tree);
}