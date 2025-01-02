#ifndef FUNCFORBST
#define FUNCFORBST

struct TreeNode {
    struct TreeNode* left;
    struct TreeNode* right;
    int val;
};

typedef struct TreeNode TreeNode;

TreeNode* createTreeNode(int val);

TreeNode* sortedArrayToBSTHelper(int arr[], int left, int right);
TreeNode* sortedArrayToBST(int arr[], int size);

int isSymmetricHelper(TreeNode* left, TreeNode* right);
int isSymmetric(TreeNode* root);

int hasPathSum(TreeNode *root, int targetSum);

TreeNode *flatten(TreeNode *root);

void printTree(TreeNode *node);
void printLevel(TreeNode *root, int level);
int height(TreeNode *root);
void printByLevel(TreeNode *root);

#endif