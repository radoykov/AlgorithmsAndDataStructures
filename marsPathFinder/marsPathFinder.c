#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "marsPathFinder.h"

Connection *createConnection(int id, int cost)
{
    Connection *newNode = (Connection *)malloc(sizeof(Connection));
    MEMORY_CHECK(newNode);
    newNode->id = id;
    newNode->cost = cost;
    newNode->next = NULL;

    return newNode;
}

void addConnectionDirectional(Graph *graph, int from, Connection *connection)
{
    connection->next = graph->adjList[from]->nextToConnection;
    graph->adjList[from]->nextToConnection = connection;
}

void addConnection(Graph *graph, int from, int to, int cost)
{
    Connection *fromConnection = createConnection(from, cost);
    Connection *toConnection = createConnection(to, cost);

    addConnectionDirectional(graph, from, toConnection);
    addConnectionDirectional(graph, to, fromConnection);
}

Node *createNode(int x, int y, int height, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    MEMORY_CHECK(newNode);
    newNode->x = x;
    newNode->y = y;
    newNode->height = height;
    newNode->value = value;

    newNode->nextToConnection = NULL;

    return newNode;
}

void addNode(Graph *graph, Node *node)
{
    graph->adjList[graph->nodesCount] = node;
    graph->nodesCount++;
}

Graph *createGraph(int nodesCount)
{
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    MEMORY_CHECK(newGraph);

    newGraph->adjList = (Node **)malloc(sizeof(Node *) * nodesCount);
    MEMORY_CHECK(newGraph->adjList);

    newGraph->nodesCount = 0;

    return newGraph;
}

Graph *readDataAndCreateGraph()
{
    FILE *file = fopen("terrain.txt", "r");
    FILE_CHECK(file);

    int nodesCount;
    fscanf(file, "%d", &nodesCount);

    Graph *graph = createGraph(nodesCount);

    int x, y, h, v;
    for (int i = 0; i < nodesCount; i++)
    {
        fscanf(file, "%d %d %d %d", &x, &y, &h, &v);
        Node *node = createNode(x, y, h, v);
        addNode(graph, node);
    }

    int connectedCount;
    fscanf(file, "%d", &connectedCount);

    int i, j, c;
    for (int x = 0; x < connectedCount; x++)
    {
        fscanf(file, "%d %d %d", &i, &j, &c);

        addConnection(graph, i, j, c);
    }
    fclose(file);

    return graph;
}

int minDistIndex(int *dist, int *visited, int size)
{
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < size; v++)
    {
        if (!visited[v] && dist[v] < min)
        {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

int caculateCost(Node* from, Node* to, Connection* edge)
{
    
    int H = abs(from->height - to->height);
    double C = sqrt(pow(from->x - to->x, 2) + pow(from->y - to->y, 2));
    double variation = (H == 0) ? 1.0 : (1.0 - C / H);

    return abs(edge->cost - to->value + variation);
}

int findPath(Graph *graph, int start, int end, int *arr)
{


    int *visited = (int *)calloc(graph->nodesCount, sizeof(int));
    MEMORY_CHECK(visited);
    int *dist = (int *)malloc(graph->nodesCount * sizeof(int));
    MEMORY_CHECK(dist);
    int *parent = (int *)calloc(graph->nodesCount, sizeof(int));
    MEMORY_CHECK(parent);

    for (int i = 0; i < graph->nodesCount; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < graph->nodesCount; i++)
    {
        int u = minDistIndex(dist, visited, graph->nodesCount); //node id

        visited[u] = 1; 
        Connection *curr = graph->adjList[u]->nextToConnection;

        while (curr)
        {
            int connCost = caculateCost(graph->adjList[u], graph->adjList[curr->id], curr); 

            if (!visited[curr->id] && dist[curr->id] > dist[u] + connCost)
            {
                dist[curr->id] = dist[u] + connCost;
                parent[curr->id] = u;
            }
            curr = curr->next;
        }

        if (visited[end] == 1) // optimization so if end is checked to stop
        {
            break;
        }
    }
    // extracting end from table
    int sizeForArr = 0;
    int *arr2 = (int *)malloc(sizeof(int) * graph->nodesCount);
    MEMORY_CHECK(arr2);

    int temp = end;
    arr2[sizeForArr++] = end;
    for (int i = 1; temp != start; i++)
    {
        arr2[i] = parent[temp];
        temp = parent[temp];
        sizeForArr++;
    }
    //arr2[sizeForArr++] = start;
    int k = sizeForArr-1;
    for (int i = 0; i < sizeForArr; i++) // invert arr in correct way
    {
        arr[i] = arr2[k--];
    }

    // free memory for arrays
    free(visited);
    free(dist);
    free(parent);
    free(arr2);

    return sizeForArr;
}
void freeProgramMemory(Graph *graph)
{
    for (int i = 0; i < graph->nodesCount; i++)
    {
        Connection *current = graph->adjList[i]->nextToConnection;
        while (current)
        {
            Connection *temp = current;
            current = current->next;
            free(temp);
        }
        free(graph->adjList[i]);
    }
    free(graph->adjList);
    free(graph);
}

void printPath(int *arr, int size, Graph *graph)
{
    printf("\nSolution : \n");
    printf("%d", arr[0]);
    for (int i = 1; i < size; i++)
    {
        printf(" -> ");
        printf("%d", arr[i]);
    }

    int sumNodes = 0;
    int sumEdges = 0;
    for (int i = 0; i < size; i++)
    {
        sumNodes += graph->adjList[arr[i]]->value;
    }
    for (int i = 0; i < size - 1; i++)
    {
        Connection *curr = graph->adjList[arr[i]]->nextToConnection;
        int nextId = arr[i + 1];

        while (curr)
        {
            if (curr->id == nextId)
            {
                sumEdges += curr->cost;
                break;
            }
            curr = curr->next;
        }
    }

    printf("\nCount of edges gone through : %d, Sum of costs of edges : %d, Sum of values of nodes : %d", size - 1, sumEdges, sumNodes);
}

void startProgram()
{
    // create graph
    Graph *graph = readDataAndCreateGraph();
    // starting the program
    int start, end;

    int *idsArr = (int *)malloc(sizeof(int) * graph->nodesCount);
    MEMORY_CHECK(idsArr);

    int exit = 0;
    while (1)
    {
        printf("\nDo you want to exit : ");
        scanf("%d", &exit);
        if (exit == 1)
        {
            freeProgramMemory(graph);
            free(idsArr);
            return;
        }

        printf("\nStart point = ");
        scanf("%d", &start);
        printf("\nEnd point = ");
        scanf("%d", &end);
        // return values
        int size = findPath(graph, start, end, idsArr);
        // printFun
        printPath(idsArr, size, graph);
    }
}
