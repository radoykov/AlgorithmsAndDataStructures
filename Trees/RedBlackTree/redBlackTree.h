#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

typedef enum Color {
    BLACK,
    RED
} Color;

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    Color color;
};

typedef struct Node Node;

Node* initNode(int val);
void leftRotation(Node** root, Node* x);
void rightRotation(Node** root, Node* y);
void treeFixUp(Node** root, Node* node);
void insert(Node**root, int val);
void printInOrder(Node* node);
void releaseTree(Node * node);


#endif