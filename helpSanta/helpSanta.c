#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpSanta.h"

int rowLength(char *maze)
{
    int len = 0;
    for (int i = 0; maze[i] != '\n'; i++)
    {
        len++;
    }
    return len;
}
char getCommand(char *maze, int x, int y)
{
    int rowLen = rowLength(maze);
    return maze[y * (rowLen + 1) + x]; //+1 for \n at the end of the row
}

int depth(Node *node, int x, int y)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->x == x && node->y == y)
    {
        return 1;
    }
    return 1 + depth(node->left, x, y) + depth(node->right, x, y) + depth(node->straight, x, y);
}

Node *findNode(Node *node, int x, int y)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->x == x && node->y == y)
    {
        return node;
    }
    Node *found = findNode(node->left, x, y);
    if (found)
        return found;

    found = findNode(node->right, x, y);
    if (found)
        return found;

    return findNode(node->straight, x, y);
}

int canInsertNode(Node *root, Node *nodeParent, int x, int y)
{
    Node *found = findNode(root, x, y);
    if (found)
    {
        if (nodeParent->depth + 1 > found->depth)
        {
            return 1;
        }
    }

    return 0;
}
Node *createNode(int x, int y, int depth)
{
    Node *node = (Node *)malloc(sizeof(Node));
    CHECK(node);
    node->left = NULL;
    node->right = NULL;
    node->straight = NULL;
    node->x = x;
    node->y = y;
    node->isExit = 0;
    node->depth = depth;

    return node;
}

Node *canNodeBeInserted(Node *root, Node *nodeParent, int x, int y, int depth)
{

    if (canInsertNode(root, nodeParent, x, y))
    {
        return NULL;
    }

    createNode(x, y, depth);
}

SantaMoves availableOptions(char command, Orientation orientation)
{
    SantaMoves moves;
    // inital proiterties so that if someone isn't writen to be udefined
    moves.first = UNDEFINED;
    moves.second = UNDEFINED; // for Z

    if (orientation == VERTICAL_UP)
    {
        switch (command)
        {
        case 'V':
            moves.first = STRAIGHT;
            moves.second = UNDEFINED;
            break;
        case 'C':
            moves.first = LEFT;
            moves.second = UNDEFINED;
            break;
        case 'D':
            moves.first = RIGHT;
            moves.second = UNDEFINED;
            break;
        case 'F':
            moves.first = STRAIGHT;
            moves.second = LEFT;
            break;
        case 'G':
            moves.first = LEFT;
            moves.second = RIGHT;
            break;
        case 'J':
            moves.first = RIGHT;
            moves.second = STRAIGHT;
            break;
        }
    }
    else if (orientation == VERTICAL_DOWN)
    {
        switch (command)
        {
        case 'V':
            moves.first = STRAIGHT;
            moves.second = UNDEFINED;
            break;
        case 'A':
            moves.first = RIGHT;
            moves.second = UNDEFINED;
            break;
        case 'B':
            moves.first = LEFT;
            moves.second = UNDEFINED;
            break;
        case 'E':
            moves.first = LEFT;
            moves.second = RIGHT;
            break;
        case 'F':
            moves.first = RIGHT;
            moves.second = STRAIGHT;
            break;
        case 'J':
            moves.first = LEFT;
            moves.second = STRAIGHT;
            break;
        }
    }
    else if (orientation == HORIZONTAL_RIGHT)
    {
        switch (command)
        {
        case 'H':
            moves.first = STRAIGHT;
            moves.second = UNDEFINED;
            break;
        case 'A':
            moves.first = LEFT;
            moves.second = UNDEFINED;
            break;
        case 'C':
            moves.first = RIGHT;
            moves.second = UNDEFINED;
            break;
        case 'E':
            moves.first = LEFT;
            moves.second = STRAIGHT;
            break;
        case 'F':
            moves.first = LEFT;
            moves.second = RIGHT;
            break;
        case 'G':
            moves.first = RIGHT;
            moves.second = STRAIGHT;
            break;
        }
    }
    else
    {
        switch (command)
        {
        case 'H':
            moves.first = STRAIGHT;
            moves.second = UNDEFINED;
            break;
        case 'B':
            moves.first = RIGHT;
            moves.second = UNDEFINED;
            break;
        case 'D':
            moves.first = LEFT;
            moves.second = UNDEFINED;
            break;
        case 'E':
            moves.first = RIGHT;
            moves.second = STRAIGHT;
            break;
        case 'G':
            moves.first = LEFT;
            moves.second = STRAIGHT;
            break;
        case 'J':
            moves.first = LEFT;
            moves.second = RIGHT;
            break;
        }
    }
    return moves;
}

void makeMove(Node *root, Node *node, char *maze, Orientation orientation, Move oneMove)
{
    if (oneMove == UNDEFINED)
    {
        return;
    }

    if (oneMove == RIGHT)
    {
        switch (orientation)
        {
        case VERTICAL_UP:
            node->right = canNodeBeInserted(root, node, node->x + 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->right, maze, HORIZONTAL_RIGHT);
            break;
        case VERTICAL_DOWN:
            node->right = canNodeBeInserted(root, node, node->x - 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->right, maze, HORIZONTAL_LEFT);
            break;
        case HORIZONTAL_LEFT:
            node->right = canNodeBeInserted(root, node, node->x, node->y - 1, node->depth + 1);
            createTreeRecursive(root, node->right, maze, VERTICAL_UP);
            break;
        case HORIZONTAL_RIGHT:
            node->right = canNodeBeInserted(root, node, node->x, node->y + 1, node->depth + 1);
            createTreeRecursive(root, node->right, maze, VERTICAL_DOWN);
            break;
        }
    }
    else if (oneMove == LEFT)
    {
        switch (orientation)
        {
        case VERTICAL_UP:
            node->left = canNodeBeInserted(root, node, node->x - 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->left, maze, HORIZONTAL_LEFT);
            break;
        case VERTICAL_DOWN:
            node->left = canNodeBeInserted(root, node, node->x + 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->left, maze, HORIZONTAL_RIGHT);
            break;
        case HORIZONTAL_LEFT:
            node->left = canNodeBeInserted(root, node, node->x, node->y + 1, node->depth + 1);

            createTreeRecursive(root, node->left, maze, VERTICAL_DOWN);
            break;
        case HORIZONTAL_RIGHT:
            node->left = canNodeBeInserted(root, node, node->x, node->y - 1, node->depth + 1);

            createTreeRecursive(root, node->left, maze, VERTICAL_UP);
            break;
        }
    }
    else
    {
        switch (orientation)
        {
        case VERTICAL_UP:
            node->straight = canNodeBeInserted(root, node, node->x, node->y - 1, node->depth + 1);
            createTreeRecursive(root, node->straight, maze, VERTICAL_UP);
            break;
        case VERTICAL_DOWN:
            node->straight = canNodeBeInserted(root, node, node->x, node->y + 1, node->depth + 1);
            createTreeRecursive(root, node->straight, maze, VERTICAL_DOWN);
            break;
        case HORIZONTAL_RIGHT:
            node->straight = canNodeBeInserted(root, node, node->x + 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->straight, maze, HORIZONTAL_RIGHT);
            break;
        case HORIZONTAL_LEFT:
            node->straight = canNodeBeInserted(root, node, node->x - 1, node->y, node->depth + 1);
            createTreeRecursive(root, node->straight, maze, HORIZONTAL_LEFT);
            break;
        }
    }
}

void createTreeRecursive(Node *root, Node *node, char *maze, Orientation orientation)
{
    if (node == NULL)
    {
        return;
    }

    if (node->x == root->x && node->y == root->y)
    {
        return;
    }
    char command = getCommand(maze, node->x, node->y);
    if (command == 'Z')
    {
        node->isExit = 1;
        return;
    }

    SantaMoves moves = availableOptions(command, orientation);

    if (moves.first != UNDEFINED)
    {
        makeMove(root, node, maze, orientation, moves.first);
    }
    if (moves.second != UNDEFINED)
    {
        makeMove(root, node, maze, orientation, moves.second);
    }
}

void searchPaths(Node *root, char *str, char *result)
{
    if (root->isExit == 1)
    {
        strcat(result, str);
        strcat(result, "\n");
        return;
    }

    if (root->left)
    {
        strcat(str, "L");
        searchPaths(root->left, str, result);
        str[strlen(str) - 1] = '\0';
    }
    if (root->right)
    {
        strcat(str, "R");
        searchPaths(root->right, str, result);
        str[strlen(str) - 1] = '\0';
    }
    if (root->straight)
    {
        strcat(str, "S");
        searchPaths(root->straight, str, result);
        str[strlen(str) - 1] = '\0';
    }
}

void freeTree(Node *root)
{
    if (!root)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    freeTree(root->straight);

    free(root);
}
char *helpSanta(char *maze, int startX, int startY)
{
    Node *root = createNode(startX, startY, 1);
    root->left = createNode(startX - 1, startY, 2);
    root->right = createNode(startX + 1, startY, 2);
    createTreeRecursive(root, root->left, maze, HORIZONTAL_LEFT);
    createTreeRecursive(root, root->right, maze, HORIZONTAL_RIGHT);
    char *str = (char *)malloc(100 * sizeof(char));
    CHECK(str);
    char *result = (char *)malloc(1000 * sizeof(char));
    CHECK(result);

    strcpy(str, "");
    strcpy(result, "");
    searchPaths(root, str, result);

    freeTree(root);
    free(str);

    return result;
}