#ifndef MARSPATHFINDER
#define MARSPATHFINDER

#define FILE_CHECK(file)              \
    if (file == NULL)                 \
    {                                 \
        printf("Cannot open file\n"); \
        exit(1);                      \
    }
#define MEMORY_CHECK(p)                     \
    if (p == NULL)                          \
    {                                       \
        printf("Cannot allocate memory\n"); \
        exit(1);                            \
    }

typedef struct Connection
{
    int id;
    int cost;
    struct Connection *next;

} Connection;

typedef struct Node
{
    int x, y;
    int height, value;
    Connection *nextToConnection;
} Node;

typedef struct Graph
{
    Node **adjList;
    int nodesCount;
} Graph;

Connection *createConnection(int id, int cost);
void addConnectionDirectional(Graph *graph, int from, Connection *connection);
void addConnection(Graph *graph, int from, int to, int cost);
Node *createNode(int x, int y, int height, int value);
void addNode(Graph *graph, Node *node);
Graph *createGraph(int nodesCount);
Graph *readDataAndCreateGraph();
int minDistIndex(int *dist, int *visited, int size);
int caculateCost(Node* from, Node* to, Connection* edge);
int findPath(Graph *graph, int start, int end, int *arr);
void freeProgramMemory(Graph *graph);
void printPath(int *arr, int size, Graph *graph);
void startProgram();

#endif