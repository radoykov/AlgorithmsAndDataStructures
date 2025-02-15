#ifndef SOLITAIRE_H
#define SOLITAIRE_H
#include "stack.h"
#define NUMBER_PILES 6
#define CHECK(p)                            \
    if (p == NULL)                          \
    {                                       \
        printf("\nError alocating memory"); \
        exit(1);                            \
    }

typedef enum Suits
{
    DIAMONDS = 0, // red КАРО
    SPADES,       // black ПИКА
    HEARTS,       // red КУПА
    CLUBS         // black Спатия
} Suits;

typedef enum Faces // the row metter
{
    _8 = 0,
    _9,
    _10,
    J,
    Q,
    K
} Faces;

typedef struct Card
{
    Faces face;
    Suits suit;

} Card;

typedef struct Move
{
    int from;
    int to;
    int CardsCountForMoving;

} Move;

typedef struct Node
{
    struct Node **pointers;
    int pointersCount;
    Move move;

} Node;

Move *createMove(int from, int to, int count);
Card *createCard(Faces face, Suits suit);
Node **cretePointers(int size);
Stack *createStack(char *str);
Node *createNode();
void *getVal(Stack *stack, int index);
int checkCards(Card *under, Card *above);
int checkCardsColours(Card *under, Card *above);
int isStackValid(Stack *stack);
int checkForSolution(Stack **arr);
void makeMove(Stack **arr, Move *move);
int getCountOfOrderedCards(Stack *stack);
int compareStack(Stack *stack, Stack *initialStack);
int compareStacks(Stack **arr, Stack **initialArr);
int searchInTree(Stack **arr, Node *root, Stack **initialArr);
void fillTheData(Move *dest, Move *sors);
Stack *checkForMovingCases(Stack **arr, Node *root, Stack **initialArr);
void undoMove(Stack **arr, Move *move);
int playPatienceRecursive(Stack **arr, Node *node, Node *root, Stack **initialArr);
Stack *copyStack(Stack *stack);
Stack **copyStacks(Stack **arr);
void releaseStacks(Stack **arr);
void releaseTree(Node *root);
int playPatience(Stack **arr);

#endif