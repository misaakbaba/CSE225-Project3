//Muhammed isa Akbaba
//150116032
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vertexSize 10
#define SIZE 40

int matrix[vertexSize][vertexSize];

struct adjNode { //
    char *name;
    int vertex;
    struct adjNode *next;
};
struct adjList {
    char *name;
    struct adjNode *head;
};
struct graphStruct {
    int vertex;
    int *visited;
    struct adjList *array;
};
struct queue {
    int items[SIZE];
    int front;
    int rear;
};

typedef struct adjNode adjNode;
typedef struct adjList adjList;
typedef struct graphStruct graphStruct;

graphStruct *graph;
int *layers;

graphStruct *initGraph(int vertex) { //function that initializes graph with is given size
    graphStruct *graph = malloc(sizeof(graphStruct));
    graph->vertex = vertex;
    graph->array = malloc(vertex * sizeof(adjList));
    graph->visited = malloc(vertexSize * sizeof(int));
//    for (int i = 0; i < vertex; ++i) {
//        graph->array[i].head=NULL;
//    }
    return graph;
}

adjNode *addAdjNode(char *name) {   //function that add node to graph
    adjNode *newNode = malloc(sizeof(struct adjNode));
    newNode->name = malloc(sizeof(name));
    strcpy(newNode->name, name);
//    newNode->next = NULL;
    return newNode;
}

adjList *addAdjList(char *name) {   //function that add node to graph
    adjList *newNode = malloc(sizeof(adjList));
    newNode->name = malloc(sizeof(name));
    strcpy(newNode->name, name);
    newNode->head = NULL;
    return newNode;
}

void
addEdge(graphStruct *graph, char *mainVertex, char *subVertex, int src, int subSrc) { //function that add edge to graph
    if (graph->array[src].head != NULL)//if there is a head, add node to stack
        if (strcmp((graph->array[src].name), mainVertex) == 0) {
            adjNode *newAdj = addAdjNode(subVertex);
            newAdj->vertex = subSrc;

            newAdj->next = graph->array[src].head;
            graph->array[src].head = newAdj;
            return;
        }
    //else add head node and add subNodes
    adjList *newList = addAdjList(mainVertex);
    graph->array[src] = *newList;
    adjNode *newAdj = addAdjNode(subVertex);
    newAdj->vertex = subSrc;
    newAdj->next = graph->array[src].head;
    graph->array[src].head = newAdj;

}

void printGraph(graphStruct *graph) {
    for (int i = 0; i < graph->vertex; ++i) {
        adjNode *node = graph->array[i].head;
        printf("\n Adjacency list of vertex %s\n head ", graph->array[i].name);
        while (node != NULL) {
            printf("-> %s", node->name);
            node = node->next;
        }
        printf("\n");
    }
}

void matrixInit() { //initialize matrix to 0
    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void matrixPrint() {
    for (int j = 0; j < vertexSize; ++j) {
        printf("%11s   ", graph->array[j].name);
    }
    puts("");
    for (int k = 0; k < vertexSize; ++k) {
        printf("%s   ", graph->array[k].name);
        for (int i = 0; i < vertexSize; ++i) {
            printf("   %d          ", matrix[k][i]);
        }
        puts("");
    }
}

void adjMatrix(graphStruct *graph) {    //print name and matrix values
    matrixInit();
    for (int i = 0; i < vertexSize; ++i) {
        adjNode *adjNode1 = graph->array[i].head;
        while (adjNode1 != NULL) {
            for (int j = 0; j < vertexSize; ++j) {
                if (strcmp(adjNode1->name, graph->array[j].name) == 0) {
                    matrix[i][j] = 1;
                    break;
                }
            }
            adjNode1 = adjNode1->next;
        }
    }
    matrixPrint();
}

void centrality(graphStruct *graph) {   //calculate centrality degrees and print
    int count, vertex = vertexSize;
    for (int i = 0; i < vertexSize; ++i) {
        count = 0;
        adjNode *node = graph->array[i].head;
        while (node != NULL) {
            count++;
            node = node->next;
        }
        printf("Degree centrality score of %s is: %d\n Standartized Score is: %d/%d", graph->array[i].name, count,
               count, vertex - 1);
        puts("\n------------------");
    }
}

struct queue *createQueue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue *q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue *q, int value) {
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
//            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if (isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for (i = q->front; i < q->rear + 1; i++) {
            printf("%d ", q->items[i]);
        }
    }
}

void resetVisited(graphStruct *graph) { //reset visited value for new iteration
    for (int i = 0; i < vertexSize; ++i) {
        graph->visited[i] = 0;
    }
}

void resetLayer() { //reset layer array for new iteration
    for (int i = 0; i < vertexSize; ++i) {
        layers[i] = 0;
    }
}

/*
 * in these function i have also calculate layer of the every node.
 * function check the current layer and set every node's layer.
 * So, i can calculate the closeness degree
 */
void bfs(graphStruct *graph, int startVertex) {
    resetLayer();
    struct queue *q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    while (!isEmpty(q)) {
//        printQueue(q);
        int current = dequeue(q);
        int layer = layers[current];
//        printf("Visited %d*\n", current);
        adjNode *node = graph->array[current].head;

        while (node) {
            int adjVertex = node->vertex;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                if (layers[adjVertex] == 0)
                    layers[adjVertex] = layer + 1;
            }
            node = node->next;
        }
    }
}

void closeness(graphStruct *graph, int vertex) {  //calculation of closeness
    int sum = 0;
    for (int i = 0; i < vertexSize; ++i) {
        sum += layers[i];
    }
    printf("Closeness of the %s is: 1/%d\n", graph->array[vertex].name, sum);
    printf("Standartized score is: 9/%d\n", sum);
    puts("---------");
    resetVisited(graph);
    resetLayer();
}


void DFS(graphStruct *graph, int master, int vertex,
         int end) { //this prototype function was for calculating the betweeness degree
    adjNode *temp = graph->array[vertex].head;


    graph->visited[vertex] = 1;

    printf("Visited %d --", vertex);
//    int vert = graph->adjLists[vertex]->vertex;
    if (vertex == end) {
//        if (vert==end){
//            graph->visited[vert] = 1;
//        }
//        printf("Visited %d --", vertex);
        puts("");
//        graph->visited[end] = 0;
        DFS(graph, master, master, end);
    }
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, master, connectedVertex, end);
        }
        temp = temp->next;
    }
}

int main() {
    graph = initGraph(10);
    addEdge(graph, "cem", "ferit", 0, 6);
    addEdge(graph, "cem", "ayse", 0, 1);
    addEdge(graph, "cem", "dundar", 0, 4);
    addEdge(graph, "ayse", "cem", 1, 0);
    addEdge(graph, "ayse", "ferit", 1, 6);
    addEdge(graph, "ayse", "dundar", 1, 4);
    addEdge(graph, "ayse", "belma", 1, 2);
    addEdge(graph, "belma", "ayse", 2, 1);
    addEdge(graph, "belma", "dundar", 2, 4);
    addEdge(graph, "belma", "edip", 2, 3);
    addEdge(graph, "edip", "belma", 3, 2);
    addEdge(graph, "edip", "dundar", 3, 4);
    addEdge(graph, "edip", "gamze", 3, 5);
    addEdge(graph, "dundar", "ayse", 4, 1);
    addEdge(graph, "dundar", "belma", 4, 2);
    addEdge(graph, "dundar", "cem", 4, 0);
    addEdge(graph, "dundar", "ferit", 4, 6);
    addEdge(graph, "dundar", "gamze", 4, 5);
    addEdge(graph, "dundar", "edip", 4, 3);
    addEdge(graph, "gamze", "dundar", 5, 4);
    addEdge(graph, "gamze", "edip", 5, 3);
    addEdge(graph, "gamze", "ferit", 5, 6);
    addEdge(graph, "gamze", "halit", 5, 7);
    addEdge(graph, "ferit", "cem", 6, 0);
    addEdge(graph, "ferit", "dundar", 6, 4);
    addEdge(graph, "ferit", "gamze", 6, 5);
    addEdge(graph, "ferit", "halit", 6, 7);
    addEdge(graph, "ferit", "ayse", 6, 1);
    addEdge(graph, "halit", "ferit", 7, 6);
    addEdge(graph, "halit", "gamze", 7, 5);
    addEdge(graph, "halit", "ilke", 7, 8);
    addEdge(graph, "ilke", "halit", 8, 7);
    addEdge(graph, "ilke", "jale", 8, 9);
    addEdge(graph, "jale", "ilke", 9, 8);
    layers = malloc(vertexSize * sizeof(int));
    printGraph(graph);
    adjMatrix(graph);
    centrality(graph);
    bfs(graph, 0);
    closeness(graph, 0);
    bfs(graph, 1);
    closeness(graph, 1);
    bfs(graph, 2);
    closeness(graph, 2);
    bfs(graph, 3);
    closeness(graph, 3);
    bfs(graph, 4);
    closeness(graph, 4);
    bfs(graph, 5);
    closeness(graph, 5);
    bfs(graph, 6);
    closeness(graph, 6);
    bfs(graph, 7);
    closeness(graph, 7);
    bfs(graph, 8);
    closeness(graph, 8);
    bfs(graph, 9);
    closeness(graph, 9);
    return 0;
}