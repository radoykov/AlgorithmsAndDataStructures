#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dynarr.h"
#include "quadTree.h"

Square *createSquare(char *name, float x, float y, float sideLen)
{
    Square *sq = (Square *)malloc(sizeof(Square));
    CHECK(sq);
    strcpy(sq->figure.name, name);
    sq->figure.type = square;
    sq->figure.centerX = x;
    sq->figure.centerY = y;
    sq->sideLength = sideLen;

    return sq;
}

Circle *createCircle(char *name, float x, float y, float radius)
{
    Circle *circ = (Circle *)malloc(sizeof(Circle));
    CHECK(circ);
    strcpy(circ->figure.name, name);
    circ->figure.type = circle;
    circ->figure.centerX = x;
    circ->figure.centerY = y;
    circ->radiusLength = radius;

    return circ;
}

int isOverlap(Figure *fig1, Figure *fig2)
{
    if (fig1->type == square && fig2->type == square)
    {
        Square *sq1 = (Square *)fig1;
        Square *sq2 = (Square *)fig2;

        float halfSizeSum = sq1->sideLength / 2 + sq2->sideLength / 2;
        float centersDistanceX = fabs(sq1->figure.centerX - sq2->figure.centerX);
        float centersDistanceY = fabs(sq1->figure.centerY - sq2->figure.centerY);

        return (centersDistanceX < halfSizeSum) && (centersDistanceY < halfSizeSum);
    }
    else if (fig1->type == circle && fig2->type == circle)
    {
        Circle *circ1 = (Circle *)fig1;
        Circle *circ2 = (Circle *)fig2;
        // d=√((x_2-x_1)²+(y_2-y_1)²)
        float distance = sqrt(pow(circ1->figure.centerX - circ2->figure.centerX, 2) + pow(circ1->figure.centerY - circ2->figure.centerY, 2));
        return distance < (circ1->radiusLength + circ2->radiusLength);
    }
    else if ((fig1->type == square && fig2->type == circle) || (fig1->type == circle && fig2->type == square))
    {

        Square *sq;
        Circle *circ;
        if (fig1->type == square && fig2->type == circle)
        {
            sq = (Square *)fig1;
            circ = (Circle *)fig2;
        }
        else
        {
            sq = (Square *)fig2;
            circ = (Circle *)fig1;
        }
        float halfSide = sq->sideLength / 2;
        float closestX = fmax(sq->figure.centerX - halfSide, fmin(circ->figure.centerX, sq->figure.centerX + halfSide));
        float closestY = fmax(sq->figure.centerY - halfSide, fmin(circ->figure.centerY, sq->figure.centerY + halfSide));
        float distance = sqrt(pow(closestX - circ->figure.centerX, 2) + pow(closestY - circ->figure.centerY, 2));
        return distance < circ->radiusLength;
    }
    return 0;
}

QuadNode *createNode(float minX, float maxX, float minY, float maxY)
{
    QuadNode *node = (QuadNode *)malloc(sizeof(QuadNode));
    CHECK(node);
    node->minX = minX;
    node->maxX = maxX;
    node->minY = minY;
    node->maxY = maxY;
    for (int i = 0; i < CHILD_NODES_MAX_COUNT; i++)
    {
        node->children[i] = NULL;
    }
    for (int i = 0; i < 10; i++)
    {
        node->figures[i] = NULL;
    }
    node->figureCount = 0;

    return node;
}
int isInRange(QuadNode *node, Figure *figure)
{
    if ((figure->centerX >= node->minX && figure->centerX <= node->maxX) &&
        (figure->centerY >= node->minY && figure->centerY <= node->maxY))
    {
        return 1;
    }
    return 0;
}

void insertFigure(QuadNode *node, Figure *figure)
{
    // find the corect node
    if (node->children[0] != NULL)
    {
        for (int i = 0; i < CHILD_NODES_MAX_COUNT; i++)
        {
            if (isInRange(node->children[i], figure))
            {
                insertFigure(node->children[i], figure);
                return;
            }
        }
    }

    // node is find and in it will be inserted
    node->figures[node->figureCount] = figure;
    node->figureCount++;
    if (node->figureCount == 10)
    {
        subDivide(node);
    }
}

void subDivide(QuadNode *node)
{
    float midX = (node->minX + node->maxX) / 2;
    float midY = (node->minY + node->maxY) / 2;
    node->children[0] = createNode(node->minX, midX, midY, node->maxY);
    node->children[1] = createNode(midX, node->maxX, midY, node->maxY);
    node->children[2] = createNode(node->minX, midX, node->minY, midY);
    node->children[3] = createNode(midX, node->maxX, node->minY, midY);
    for (int i = 0; i < node->figureCount; i++)
    {
        insertFigure(node, node->figures[i]);
    }
}

QuadNode *buildTree(Figure **figures, int count)
{
    QuadNode *root = createNode(-1000, 1000, -1000, 1000);
    for (int i = 0; i < count; i++)
    {
        insertFigure(root, figures[i]);
    }
    return root;
}

int areQuadsAdjacent(QuadNode *a, QuadNode *b)
{
    int verticalAdjacent = (a->maxX == b->minX || a->minX == b->maxX);

    int horizontalAdjacent = (a->maxY == b->minY || a->minY == b->maxY);

    int cornerAdjacent = ((a->maxX == b->minX || a->minX == b->maxX) &&
                          (a->maxY == b->minY || a->minY == b->maxY));

    return verticalAdjacent || horizontalAdjacent || cornerAdjacent;
}

void insertOverlappedFigures(Figure *f1, Figure *f2, DynamicArray *overlaps)
{
    Overlapped *overlapped = (Overlapped *)malloc(sizeof(Overlapped));
    CHECK(overlapped);
    overlapped->figure1 = f1;
    overlapped->figure2 = f2;
    pushBack(overlaps, overlapped);
}

void checkOverlapsInNode(QuadNode *node, DynamicArray *overlaps)
{
    for (int i = 0; i < node->figureCount; i++)
    {
        for (int j = i + 1; j < node->figureCount; j++)
        {
            if (isOverlap(node->figures[i], node->figures[j]))
            {
                insertOverlappedFigures(node->figures[i], node->figures[j], overlaps);
                // printf("\n-Overlap between %s and %s", node->figures[i]->name, node->figures[j]->name);
            }
        }
    }
}

void checkOverlapsWithNeighbors(QuadNode *node, QuadNode *neighbor, DynamicArray *overlaps)
{
    for (int i = 0; i < node->figureCount; i++)
    {
        for (int j = 0; j < neighbor->figureCount; j++)
        {
            if (isOverlap(node->figures[i], neighbor->figures[j]))
            {
                insertOverlappedFigures(node->figures[i], neighbor->figures[j], overlaps);
                // printf("\n-Overlap between %s and %s", node->figures[i]->name, neighbor->figures[j]->name);
            }
        }
    }
}

void findAdjacentQuadsReqursive(QuadNode *baseNode, QuadNode *node, DynamicArray *checkedNodes, DynamicArray *overlaps)
{
    if (baseNode == node || contains(checkedNodes, node))
    {
        return;
    }

    // node is leaf
    if (node->children[0] == NULL)
    {
        if (areQuadsAdjacent(node, baseNode))
        {
            checkOverlapsWithNeighbors(node, baseNode, overlaps);
        }
    }
    else
    {
        for (int i = 0; i < CHILD_NODES_MAX_COUNT; i++)
        {
            findAdjacentQuadsReqursive(baseNode, node->children[i], checkedNodes, overlaps);
        }
    }
}

void findOverlapsRecursive(QuadNode *node, QuadNode *root, DynamicArray *checkedNodes, DynamicArray *overlaps)
{
    if (node->children[0] == NULL)
    {
        checkOverlapsInNode(node, overlaps);
        findAdjacentQuadsReqursive(node, root, checkedNodes, overlaps);
        pushBack(checkedNodes, node);
    }
    else
    {
        for (int i = 0; i < CHILD_NODES_MAX_COUNT; i++)
        {
            findOverlapsRecursive(node->children[i], root, checkedNodes, overlaps);
        }
    }
}

void releaseAll(DynamicArray arr)
{
    for (uint i = 0; i < arr.size; i++)
    {
        free(arr.buffer[i]); // Free each Overlapped object
    }
    release(&arr);
}

DynamicArray findOverlaps(QuadNode *root)
{
    DynamicArray checkedNodes = init(0);
    DynamicArray overlaps = init(0);
    findOverlapsRecursive(root, root, &checkedNodes, &overlaps);
    releaseAll(checkedNodes);

    return overlaps;
}