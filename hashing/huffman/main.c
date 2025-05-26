#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

typedef struct HuffmanTreeNode
{
    char c;
    int freq;
    struct HuffmanTreeNode *left;
    struct HuffmanTreeNode *right;
} HuffmanTreeNode;

HuffmanTreeNode *initHuffmanTreeNode(char c, int freq)
{
    HuffmanTreeNode *newNode = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
    CHECK(newNode);
    newNode->c = c;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

HuffmanTreeNode *huffmanTree(char *text)
{
    int freq[256] = {0};
    for (int i = 0; text[i] != '\0'; i++)
    {
        freq[text[i]]++;
    }

    PQueue *pq = initPQ();

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            HuffmanTreeNode *node = initHuffmanTreeNode(i, freq[i]);
            pqInsert(pq, node, freq[i]);
        }
    }

    while (pq->size > 1)
    {
        HuffmanTreeNode *left = (HuffmanTreeNode *)deleteMin(pq)->data;
        HuffmanTreeNode *right = (HuffmanTreeNode *)deleteMin(pq)->data;

        HuffmanTreeNode *parent = initHuffmanTreeNode(0, left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        pqInsert(pq, parent, parent->freq);
    }
    HuffmanTreeNode * hn = deleteMin(pq)->data;
    freePQ(pq);
    return hn;
}

void printCodes(HuffmanTreeNode *root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right)
    {
        printf("%c, %d: ", root->c, root->freq);
        for (int i = 0; i < top; i++)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void encodeHuffmanHelper(HuffmanTreeNode *root, char ch, int arr[], int arrSize)
{
    if (ch == root->c)
    {
        for (int i = 0; i < arrSize; i++)
        {
            printf("%d", arr[i]);
        }
        arrSize = 0;
    }
    if (root->left)
    {
        arr[arrSize++] = 0;
        encodeHuffmanHelper(root->left, ch, arr, arrSize);
        arrSize--;
    }
    if (root->right)
    {
        arr[arrSize++] = 1;
        encodeHuffmanHelper(root->right, ch, arr, arrSize);
        arrSize--;
    }
}

void encodeHuffman(HuffmanTreeNode *root, char *name)
{
    int arr[100]; ///\for one char
    int arrSize = 0;
    int nameLen = strlen(name);
    for (int i = 0; i < nameLen; i++)
    {
        encodeHuffmanHelper(root, name[i], arr, arrSize);
    }
}
void decodeHuffman(HuffmanTreeNode *rootOriginal, HuffmanTreeNode *root, int code[], int startIndex, int codeSize)
{
    // bottom of rec.
    if (!root->left && !root->right)
    {
        printf("%c", root->c);
        decodeHuffman(rootOriginal, rootOriginal, code, startIndex, codeSize);
        return;
    }
    if (startIndex >= codeSize)
    {
        return;
    }

    if (code[startIndex] == 0 && root->left)
    {
        decodeHuffman(rootOriginal, root->left, code, startIndex + 1, codeSize);
    }
    else if (code[startIndex] == 1 && root->right)
    {
        decodeHuffman(rootOriginal, root->right, code, startIndex + 1, codeSize);
    }
}

void freeHuffmanTree(HuffmanTreeNode *node)
{
    if (!node)
    {
        return;
    }
    freeHuffmanTree(node->left);
    freeHuffmanTree(node->right);
    free(node);
}

int main()
{
    // char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec hendrerit lectus vitae tellus congue dapibus. Cras auctor auctor pellentesque. Phasellus consequat lacus ipsum. Maecenas sit amet massa lacinia, malesuada diam in, gravida odio. Sed consequat lorem tortor, elementum ornare enim gravida sed. In molestie condimentum sapien, vel finibus turpis eleifend semper. Nam ac lorem rhoncus, pellentesque dui a, tincidunt lectus. Ut fermentum velit gravida neque condimentum, sed porttitor nunc facilisis. Donec rhoncus ornare venenatis. Quisque sed placerat felis, ac laoreet ante. Quisque sit amet ipsum ac quam imperdiet volutpat vitae id ipsum.";
    char text[] = "AAAABBBVGGDKKK";
    HuffmanTreeNode *root = huffmanTree(text);
    int arr[100];
    int top = 0;
    printCodes(root, arr, top);
    encodeHuffman(root, text);

    int code[8] = {0, 1, 1, 1, 1, 0, 1, 0};
    decodeHuffman(root, root, code, 0, 8);
    freeHuffmanTree(root);
}