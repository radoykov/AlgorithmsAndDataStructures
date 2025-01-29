#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int isExit;
} Node;

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

Node *createNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->straight = NULL;
    node->isExit = 0;

    return node;
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
void createTreeRecursive(Node *node, char *maze, int xBase, int yBase, int x, int y, Orientation orientation);

void makeMove(Node *node, char *maze, int xBase, int yBase, int x, int y, Orientation orientation, Move oneMove)
{
    if (oneMove == UNDEFINED)
    {
        return;
    }

    if (oneMove == RIGHT)
    {
        node->right = createNode();
        switch (orientation)
        {
        case VERTICAL_UP:
            createTreeRecursive(node->right, maze, xBase, yBase, x + 1, y, HORIZONTAL_RIGHT);
            break;
        case VERTICAL_DOWN:
            createTreeRecursive(node->right, maze, xBase, yBase, x - 1, y, HORIZONTAL_LEFT);
            break;
        case HORIZONTAL_LEFT:
            createTreeRecursive(node->right, maze, xBase, yBase, x, y - 1, VERTICAL_UP);
            break;
        case HORIZONTAL_RIGHT:
            createTreeRecursive(node->right, maze, xBase, yBase, x, y + 1, VERTICAL_DOWN);
            break;
        }
    }
    else if (oneMove == LEFT)
    {
        node->left = createNode();
        switch (orientation)
        {
        case VERTICAL_UP:
            createTreeRecursive(node->left, maze, xBase, yBase, x - 1, y, HORIZONTAL_LEFT);
            break;
        case VERTICAL_DOWN:
            createTreeRecursive(node->left, maze, xBase, yBase, x + 1, y, HORIZONTAL_RIGHT);
            break;
        case HORIZONTAL_LEFT:
            createTreeRecursive(node->left, maze, xBase, yBase, x, y + 1, VERTICAL_DOWN);
            break;
        case HORIZONTAL_RIGHT:
            createTreeRecursive(node->left, maze, xBase, yBase, x, y - 1, VERTICAL_UP);
            break;
        }
    }
    else
    {
        node->straight = createNode();
        switch (orientation)
        {
        case VERTICAL_UP:
            createTreeRecursive(node->straight, maze, xBase, yBase, x, y - 1, VERTICAL_UP);
            break;
        case VERTICAL_DOWN:
            createTreeRecursive(node->straight, maze, xBase, yBase, x, y + 1, VERTICAL_DOWN);
            break;
        case HORIZONTAL_RIGHT:
            createTreeRecursive(node->straight, maze, xBase, yBase, x + 1, y, HORIZONTAL_RIGHT);
            break;
        case HORIZONTAL_LEFT:
            createTreeRecursive(node->straight, maze, xBase, yBase, x - 1, y, HORIZONTAL_LEFT);
            break;
        }
    }
}

int checkForTimesNodeIsAdded(node)
{
    
}

void createTreeRecursive(Node *node, char *maze, int xBase, int yBase, int x, int y, Orientation orientation)
{
    if(checkForTimesNodeIsAdded(node) == 1){
        return;
    }

    if (x == xBase && y == yBase)
    {
        return;
    }
    char command = getCommand(maze, x, y);
    if (command == 'Z')
    {
        node->isExit = 1;
        return;
    }

    SantaMoves moves = availableOptions(command, orientation);
    // printf("x: %d, y: %d, command: %c, orientation: %d\n", x, y, command, orientation);

    if (moves.first != UNDEFINED)
    {
        makeMove(node, maze, xBase, yBase, x, y, orientation, moves.first);
    }
    if (moves.second != UNDEFINED)
    {
        makeMove(node, maze, xBase, yBase, x, y, orientation, moves.second);
    }
}

void searchPaths(Node *root, char *str, char *result)
{
    if (root->isExit == 1)
    {
        strcat(result, str);
        strcat(result, "\n");
        strcpy(str, "");
        return;
    }

    if (root->left != NULL)
    {
        strcat(str, "L");
        searchPaths(root->left, str, result);
    }
    if (root->right != NULL)
    {
        strcat(str, "R");
        searchPaths(root->right, str, result);
    }
    if (root->straight != NULL)
    {
        strcat(str, "S");
        searchPaths(root->straight, str, result);
    }
    strcpy(str, "");
}

char *helpSanta(char *maze, int startX, int startY)
{
    Node *root = createNode();
    root->left = createNode();
    root->right = createNode();
    createTreeRecursive(root->left, maze, startX, startY, startX - 1, startY, HORIZONTAL_LEFT);
    createTreeRecursive(root->right, maze, startX, startY, startX + 1, startY, HORIZONTAL_RIGHT);
    char *str = (char *)malloc(100 * sizeof(char));
    char *result = (char *)malloc(1000 * sizeof(char));
    strcpy(str, "");
    strcpy(result, "");
    searchPaths(root, str, result);
    return result;
}

int main()
{
    // char *maze = "XXZDC\nXDEAV\nDAXDA\nVDHAX\nBAXXX\n\0";
    // char *solution = helpSanta(maze, 2, 3);
    // printf("%s", solution);

    char *maze = "DHCXDHHCXX\nVXBGEXXVXX\nBCXJCXDAXX\nZFDAVXBGHC\nDEEHFXXVXV\nVXDHFXXBHF\nVXVXBHDXXV\nBHAXXXBHHA\0";
    char *solution = helpSanta(maze, 8, 5);
    printf("%s", solution);

    return 0;
}
/*
XXZ╔╗
X╔╩╝║
╔╝X╔╝
║╔═╝X <= Santa is above first X , which is in row with 2 others.
╚╝XXX
*/

/*
╔═╗x╔══╗xx
║x╚╦╩xx║xx
╚╗x╠╗x╔╝xx
Z╣╔╝║x╚╦═╗
╔╩╩═╣xx║x║
║x╔═╣xx╚═╣<= Santa is above second X , which is in row with 2 others.
║x║x╚═╗xx║
╚═╝xxx╚══╝
*/