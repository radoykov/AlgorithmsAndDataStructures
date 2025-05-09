#include <stdio.h>
#include <stdlib.h>
#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct Edge
{
    int from;
    int to;
    int weight;
} Edge;

typedef struct Graph
{
    Edge *edges;
    int edgeCount;
    int vertexCount;
} Graph;

typedef struct DisjointSet
{
    int *parent;
} DisjointSet;

//vertex or node is the same 

DisjointSet *initDisjointSet(int vertexCount)
{
    DisjointSet *djs = (DisjointSet *)malloc(sizeof(DisjointSet));
    CHECK(djs);
    djs->parent = (int *)malloc(sizeof(int) * vertexCount);
    CHECK(djs->parent);
    for (int i = 0; i < vertexCount; i++)
    {
        djs->parent[i] = i;
    }
    return djs;
}

int find(DisjointSet *djs, int vertex)
{
    if (djs->parent[vertex] == vertex)
    {
        return vertex;
    }

    return find(djs, djs->parent[vertex]);
}

void uniteSet(DisjointSet *djs, int vertex1, int vertex2)
{
    int root1 = find(djs, vertex1);
    int root2 = find(djs, vertex2);

    djs->parent[root1] = root2;
}

int compareEdge(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;

    return e1->weight - e2->weight;
}

void kruskals(Graph *graph)
{
    Edge *result = (Edge *)malloc(sizeof(Edge) * (graph->vertexCount - 1));
    CHECK(result);
    DisjointSet *djs = initDisjointSet(graph->vertexCount);
    int mstEdgeCount = 0;
    qsort(graph->edges, graph->edgeCount, sizeof(Edge), compareEdge);

    for (int i = 0; i < graph->edgeCount; i++)
    {
        int root1 = find(djs, graph->edges[i].from);
        int root2 = find(djs, graph->edges[i].to);

        if (root1 != root2)
        {
            result[mstEdgeCount++] = graph->edges[i];
            uniteSet(djs, graph->edges[i].from, graph->edges[i].to);

            if (mstEdgeCount == graph->vertexCount - 1)
            {
                break;
            }
        }
    }

    printf("Edges in MST:\n");

    int mstWeight = 0;
    for (int i = 0; i < mstEdgeCount; i++)
    {
        printf("%d - %d\tWeight: %d \n", result[i].from, result[i].to, result[i].weight);
        mstWeight += result[i].weight;
    }

    printf("Total weight: %d", mstWeight);

    free(result);
    free(djs->parent);
    free(djs);
}

int main()
{
    int V = 4;
    int E = 5;

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    CHECK(graph);
    graph->vertexCount = V;
    graph->edgeCount = E;
    graph->edges = (Edge *)malloc(sizeof(Edge) * E);
    CHECK(graph->edges);

    // Add edges (example)
    // edge 0: 0-1, weight 10
    graph->edges[0].from = 0;
    graph->edges[0].to = 1;
    graph->edges[0].weight = 10;

    // edge 1: 0-2, weight 6
    graph->edges[1].from = 0;
    graph->edges[1].to = 2;
    graph->edges[1].weight = 6;

    // edge 2: 0-3, weight 5
    graph->edges[2].from = 0;
    graph->edges[2].to = 3;
    graph->edges[2].weight = 5;

    // edge 3: 1-3, weight 15
    graph->edges[3].from = 1;
    graph->edges[3].to = 3;
    graph->edges[3].weight = 15;

    // edge 4: 2-3, weight 4
    graph->edges[4].from = 2;
    graph->edges[4].to = 3;
    graph->edges[4].weight = 4;

    // Run Kruskal's algorithm
    kruskals(graph);

    // Clean up memory allocated in main
    free(graph->edges);
    free(graph);

    return 0;
}