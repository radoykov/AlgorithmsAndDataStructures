#ifndef HELP_SANTA_H
#define HELP_SANTA_H

#define CHECK(p)                            \
    if (p == NULL)                          \
    {                                       \
        printf("\nError alocating memory"); \
        exit(1);                            \
    }

typedef enum move
{
    LEFT,
    RIGHT,
    STRAIGHT,
    UNDEFINED
} Move;

typedef enum orientation
{
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT,
    VERTICAL_UP,
    VERTICAL_DOWN
} Orientation;

typedef struct SantaMoves
{
    Move first;
    Move second;

} SantaMoves;

typedef struct Node
{
    struct Node *left;
    struct Node *straight;
    struct Node *right;
    int x;
    int y;
    int isExit;
    int depth;
} Node;

int rowLength(char *maze);
char getCommand(char *maze, int x, int y);
int depth(Node *node, int x, int y);
Node *findNode(Node *node, int x, int y);
int canInsertNode(Node *root, Node *nodeParent, int x, int y);
Node *createNode(int x, int y, int depth);
Node *canNodeBeInserted(Node *root, Node *nodeParent, int x, int y, int depth);
SantaMoves availableOptions(char command, Orientation orientation);
void makeMove(Node *root, Node *node, char *maze, Orientation orientation, Move oneMove);
void createTreeRecursive(Node *root, Node *node, char *maze, Orientation orientation);
void searchPaths(Node *root, char *str, char *result);
void freeTree(Node *root);
char *helpSanta(char *maze, int startX, int startY);

#endif