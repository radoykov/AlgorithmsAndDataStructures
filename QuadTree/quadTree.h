#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#define CHILD_NODES_MAX_COUNT 4
#define MAX_FIGURES_PER_QUAD 10
#define FIGURE_NAME_MAX_LENGTH 50

#include "dynarr.h"
typedef enum
{
    square = 0,
    circle = 1
} Type;

typedef struct
{
    char name[FIGURE_NAME_MAX_LENGTH];
    Type type;
    float centerX;
    float centerY;

} Figure;

typedef struct
{
    Figure figure;
    float sideLength;

} Square;

typedef struct
{
    Figure figure;
    float radiusLength;

} Circle;

typedef struct QuadNode
{
    float minX, maxX, minY, maxY;
    struct QuadNode *children[CHILD_NODES_MAX_COUNT];
    Figure *figures[MAX_FIGURES_PER_QUAD];
    int figureCount;

} QuadNode;

typedef struct overlapped
{
    Figure *figure1;
    Figure *figure2;
} Overlapped;

Square *createSquare(char *name, float x, float y, float sideLen);
Circle *createCircle(char *name, float x, float y, float radius);
int isOverlap(Figure *fig1, Figure *fig2);
QuadNode *createNode(float minX, float maxX, float minY, float maxY);
int isInRange(QuadNode *node, Figure *figure);
void insertFigure(QuadNode *node, Figure *figure);
void subDivide(QuadNode *node);
QuadNode *buildTree(Figure **figures, int count);
int areQuadsAdjacent(QuadNode *a, QuadNode *b);
void insertOverlappedFigures(Figure *f1, Figure *f2, DynamicArray *overlaps);
void checkOverlapsInNode(QuadNode *node, DynamicArray *overlaps);
void checkOverlapsWithNeighbors(QuadNode *node, QuadNode *neighbor, DynamicArray *overlaps);
void findAdjacentQuadsReqursive(QuadNode *baseNode, QuadNode *node, DynamicArray *checkedNodes, DynamicArray *overlaps);
void findOverlapsRecursive(QuadNode *node, QuadNode *root, DynamicArray *checkedNodes, DynamicArray *overlaps);
void releaseAll(DynamicArray arr);
DynamicArray findOverlaps(QuadNode *root);

#endif