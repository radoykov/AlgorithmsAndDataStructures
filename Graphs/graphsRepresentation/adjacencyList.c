#include <stdio.h>
#include <stdlib.h>

#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

typedef struct Graph
{
    int nodeCount;
    Node **adjList;
} Graph;

Node *initNode(int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    CHECK(newNode);

    newNode->val = val;
    newNode->next = NULL;

    return newNode;
}

Graph *initGraph(int nodeCount)
{
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    CHECK(newGraph);

    newGraph->nodeCount = nodeCount;
    newGraph->adjList = (Node **)calloc(nodeCount, sizeof(Node *));
    CHECK(newGraph->adjList);

    return newGraph;
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->nodeCount; i++)
    {
        Node *curr = graph->adjList[i];
        Node *temp = NULL;
        while (curr)
        {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjList); 
    free(graph);
}

void addEdgeDirectional(Graph *graph, int from, int to)
{
    Node *newNode = initNode(to);
    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;
}

void addEdge(Graph *graph, int node1, int node2)
{
    addEdgeDirectional(graph, node1, node2);
    addEdgeDirectional(graph, node2, node1);
}

void printGraph(Graph *graph)
{

    for (int i = 0; i < graph->nodeCount; i++)
    {
        printf("Neighbors of %d: ", i);
        Node *curr = graph->adjList[i];
        while (curr)
        {
            printf("%d ", curr->val);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main()
{
    Graph *graph = initGraph(6);
    addEdgeDirectional(graph, 0, 5);
    addEdgeDirectional(graph, 4, 0);
    addEdge(graph, 0, 3);
    addEdge(graph, 4, 3);
    addEdge(graph, 1, 5);
    addEdge(graph, 4, 1);
    addEdge(graph, 4, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 5, 2);

    printGraph(graph);

    freeGraph(graph);
}