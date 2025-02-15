#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solitaire.h"

Move *createMove(int from, int to, int count)
{
    Move *move = (Move *)malloc(sizeof(Move));
    CHECK(move);

    move->from = from;
    move->to = to;
    move->CardsCountForMoving = count;

    return move;
}

Card *createCard(Faces face, Suits suit)
{
    Card *card = (Card *)malloc(sizeof(Card));
    CHECK(card);
    card->face = face;
    card->suit = suit;

    return card;
}

// void releaseStackOfCards(Stack *stack);
Node **cretePointers(int size)
{
    if (!size)
    {
        return NULL;
    }
    Node **pointers = (Node **)malloc(sizeof(Node *) * size);
    CHECK(pointers);

    for (int i = 0; i < size; i++)
    {
        pointers[i] = NULL;
    }
    return pointers;
}

Stack *createStack(char *str)
{
    Stack *stack = initStack();
    int i = 0;
    while (str[i] != '\0')
    {
        Faces face;
        switch (str[i])
        {
        case 'K':
            face = K;
            break;
        case 'Q':
            face = Q;
            break;
        case 'J':
            face = J;
            break;
        case '1':
            face = _10;
            break;
        case '9':
            face = _9;
            break;
        case '8':
            face = _8;
            break;
        }
        i++;
        Suits suit;
        switch (str[i])
        {
        case 'D':
            suit = DIAMONDS;
            break;
        case 'S':
            suit = SPADES;
            break;
        case 'H':
            suit = HEARTS;
            break;
        case 'C':
            suit = CLUBS;
        }

        Card *card = createCard(face, suit);
        pushStack(stack, card);

        i += 2;
    }

    return stack;
}
Node *createNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    CHECK(node);
    node->pointers = NULL;
    node->pointersCount = 0;
    node->move.CardsCountForMoving = 0;
    node->move.from = 0;
    node->move.to = 0;

    return node;
}

void *getVal(Stack *stack, int index)
{
    if (!stack->top)
    {
        return NULL;
    }
    StackNode *p = stack->top;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        if (!p)
        {
            return NULL;
        }
    }

    return p->val;
}

int checkCards(Card *under, Card *above)
{
    if (!under && !above)
    {
        return 1;
    }
    if (!under || !above)
    {
        return 0;
    }

    if (under->suit == above->suit && above->face == under->face)
    {
        return 1;
    }
    return 0;
}

int checkCardsColours(Card *under, Card *above)
{
    if (!under && !above)
    {
        return 1;
    }

    if (!under || !above)
    {
        return 0;
    }

    if (under->suit % 2 == above->suit % 2)
    {
        return 0;
    }

    if (above->face + 1 == under->face)
    {
        return 1;
    }
    return 0;
}

int isStackValid(Stack *stack)
{
    if (!stack->top)
    {
        return 1;
    }
    if (stack->size != 6) // Check the number of cards.
    {
        return 0;
    }
    for (int i = 0; i < NUMBER_PILES - 1; i++) // count for checking
    {
        Card *up = getVal(stack, i);
        Card *down = getVal(stack, i + 1);

        if (!checkCardsColours(down, up))
        {
            return 0;
        }
    }
    return 1;
}

int checkForSolution(Stack **arr)
{
    for (int i = 0; i < NUMBER_PILES; i++)
    {
        if (!isStackValid(arr[i]))
        {
            return 0;
        }
    }
    return 1;
}

void makeMove(Stack **arr, Move *move)
{
    if (move->to == 0 && move->from == 0)
    {
        return;
    }
    Stack *from = arr[move->from];
    Stack *to = arr[move->to];

    if (move->CardsCountForMoving == 1)
    {
        pushStack(to, popStack(from));
        return;
    }

    Stack *buffer = initStack();

    for (int i = 0; i < move->CardsCountForMoving; i++)
    {
        pushStack(buffer, popStack(from));
    }
    for (int i = 0; i < move->CardsCountForMoving; i++)
    {
        pushStack(to, popStack(buffer));
    }
    releaseStack(buffer);
}

int getCountOfOrderedCards(Stack *stack)
{
    if (stack->top == NULL)
    {
        return 0;
    }
    for (int i = 0; i < NUMBER_PILES; i++)
    {
        if (!checkCardsColours(getVal(stack, i + 1), getVal(stack, i)))
        {
            return i + 1;
        }
    }
    return NUMBER_PILES;
}

int compareStack(Stack *stack, Stack *initialStack)
{

    if (stack->size != initialStack->size)
    {
        return 0;
    }

    for (int i = 0; i < stack->size; i++)
    {
        if (!checkCards(getVal(stack, i), getVal(initialStack, i)))
        {
            return 0;
        }
    }
    return 1;
}

int compareStacks(Stack **arr, Stack **initialArr)
{

    for (int i = 0; i < NUMBER_PILES; i++)
    {
        if (!compareStack(arr[i], initialArr[i]))
        {
            return 0;
        }
    }

    return 1;
}
// void undoMove(Stack **arr, Move *move);
int searchInTree(Stack **arr, Node *root, Stack **initialArr)
{
    if (!root)
    {
        return 0;
    }
    makeMove(initialArr, &root->move);

    if (compareStacks(arr, initialArr))
    {
        undoMove(initialArr, &root->move);
        return 1;
    }

    int solve = 0;
    for (int i = 0; i < root->pointersCount; i++)
    {
        solve = solve || searchInTree(arr, root->pointers[i], initialArr);
    }
    undoMove(initialArr, &root->move);
    return solve;
}

Stack *checkForMovingCases(Stack **arr, Node *root, Stack **initialArr)
{
    Stack *result = initStack();

    // get through all cards
    for (int i = 0; i < NUMBER_PILES; i++)
    {
        Stack *currentStack = arr[i];

        for (int k = 0; k < NUMBER_PILES; k++)
        {
            if (i == k)
            {
                continue;
            }
            Stack *nextStack = arr[k];
            // Up to there we have 2 stacks and have to check if we ncan make move from left ro right.

            int count = getCountOfOrderedCards(currentStack);

            if (count == 0)
            {
                continue;
            }
            Card *upperCardInNextStack = getVal(nextStack, 0);
            Card *currentCard = getVal(currentStack, count - 1);

            if (checkCardsColours(upperCardInNextStack, currentCard) || !upperCardInNextStack)
            {
                Move *move = createMove(i, k, count);

                // if it exist somewhere in tree
                makeMove(arr, move);
                if (searchInTree(arr, root, initialArr))
                {
                    undoMove(arr, move);
                    free(move);
                    continue;
                }
                undoMove(arr, move);

                pushStack(result, move);
            }
        }
    }

    return result;
}

void fillTheData(Move *dest, Move *sors)
{
    dest->to = sors->to;
    dest->from = sors->from;
    dest->CardsCountForMoving = sors->CardsCountForMoving;
}

void undoMove(Stack **arr, Move *move)
{
    Move *current = createMove(move->to, move->from, move->CardsCountForMoving);

    makeMove(arr, current);
    free(current);
}

int playPatienceRecursive(Stack **arr, Node *node, Node *root, Stack **initialArr)
{
    printf("\n%d,%d,%d", node->move.from, node->move.to, node->move.CardsCountForMoving);
    // if it is NULL then return 0, so we have to do nothing.
    if (!node)
    {
        return 0;
    }
    if (checkForSolution(arr))
    {
        return 1;
    }
    // if isn't we have to execute the comand in the node.
    makeMove(arr, &node->move); // from and to are indexes!
    printf("\n%d,%d,%d,%d,%d,%d", arr[0]->size, arr[1]->size, arr[2]->size, arr[3]->size, arr[4]->size, arr[5]->size);
    // Therefore, have to check the possible movements and that function will return it like a stack of other structure & get a size of it.
    Stack *moves = checkForMovingCases(arr, root, initialArr);
    // Then get throuhg the all childs of it and make it and call a functio recursive.
    node->pointersCount = moves->size;
    node->pointers = cretePointers(node->pointersCount);
    int isSolved = 0;
    for (int i = 0; i < node->pointersCount; i++)
    {
        node->pointers[i] = createNode();
        fillTheData(&node->pointers[i]->move, popStack(moves));
        isSolved = isSolved || playPatienceRecursive(arr, node->pointers[i], root, initialArr);
    }
    releaseStack(moves);
    undoMove(arr, &node->move);

    return isSolved;
}

Stack *copyStack(Stack *stack)
{
    Stack *newStack = initStack();
    for (int i = 0; i < stack->size; i++)
    {

        Card *currentCard = getVal(stack, stack->size - i - 1);
        Card *newCard = createCard(currentCard->face, currentCard->suit);
        pushStack(newStack, newCard);
    }
    return newStack;
}

Stack **copyStacks(Stack **arr)
{
    Stack **newArr = malloc(sizeof(Stack *) * NUMBER_PILES);

    for (int i = 0; i < NUMBER_PILES; i++)
    {
        newArr[i] = copyStack(arr[i]);
    }

    return newArr;
}

void releaseStacks(Stack **arr)
{
    for (int i = 0; i < NUMBER_PILES; i++)
    {
        releaseStack(arr[i]);
    }
    free(arr);
}

void releaseTree(Node *root)
{
    if (!root)
    {
        return;
    }
    for (int i = 0; i < root->pointersCount; i++)
    {
        releaseTree(root->pointers[i]);
    }
    free(root->pointers); // Free the array itself
    free(root);
}

int playPatience(Stack **arr)
{
    Node *root = createNode();
    Stack **copyArr = copyStacks(arr);

    int res = playPatienceRecursive(arr, root, root, copyArr);
    releaseStacks(copyArr);
    releaseTree(root);
    return res;
}