#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vertexSize 10

int matrix[vertexSize][vertexSize];

struct adjNode {
    char *name;
    struct adjNode *next;
};
struct adjList {
    char *name;
    struct adjNode *head;
};
struct graphStruct {
    int vertex;
    struct adjList *array;
};
typedef struct adjNode adjNode;
typedef struct adjList adjList;
typedef struct graphStruct graphStruct;

graphStruct *graph;


graphStruct *initGraph(int vertex) {
    graphStruct *graph = malloc(sizeof(graphStruct));
    graph->vertex = vertex;
    graph->array = malloc(vertex * sizeof(adjList));
//    for (int i = 0; i < vertex; ++i) {
//        graph->array[i].head=NULL;
//    }
    return graph;
}

adjNode *addAdjNode(char *name) {
    adjNode *newNode = malloc(sizeof(struct adjNode));
    newNode->name = malloc(sizeof(name));
    strcpy(newNode->name, name);
//    newNode->next = NULL;
    return newNode;
}

adjList *addAdjList(char *name) {
    adjList *newNode = malloc(sizeof(adjList));
    newNode->name = malloc(sizeof(name));
    strcpy(newNode->name, name);
    newNode->head = NULL;
    return newNode;
}

void addEdge(graphStruct *graph, char *mainVertex, char *subVertex, int src) {
    if (graph->array[src].head != NULL)
        if (strcmp((graph->array[src].name), mainVertex) == 0) {
            adjNode *newAdj = addAdjNode(subVertex);

            newAdj->next = graph->array[src].head;
            graph->array[src].head = newAdj;
            return;
        }
    adjList *newList = addAdjList(mainVertex);
    graph->array[src] = *newList;
    adjNode *newAdj = addAdjNode(subVertex);

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

void matrixInit() {
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

void adjMatrix(graphStruct *graph) {
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

void centrality(graphStruct *graph) {
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


int main() {
    graph = initGraph(10);
    addEdge(graph, "cem", "ferit", 0);
    addEdge(graph, "cem", "ayse", 0);
    addEdge(graph, "cem", "dundar", 0);
    addEdge(graph, "ayse", "cem", 1);
    addEdge(graph, "ayse", "ferit", 1);
    addEdge(graph, "ayse", "dundar", 1);
    addEdge(graph, "ayse", "belma", 1);
    addEdge(graph, "belma", "ayse", 2);
    addEdge(graph, "belma", "dundar", 2);
    addEdge(graph, "belma", "edip", 2);
    addEdge(graph, "edip", "belma", 3);
    addEdge(graph, "edip", "dundar", 3);
    addEdge(graph, "edip", "gamze", 3);
    addEdge(graph, "dundar", "ayse", 4);
    addEdge(graph, "dundar", "belma", 4);
    addEdge(graph, "dundar", "cem", 4);
    addEdge(graph, "dundar", "ferit", 4);
    addEdge(graph, "dundar", "gamze", 4);
    addEdge(graph, "dundar", "edip", 4);
    addEdge(graph, "gamze", "dundar", 5);
    addEdge(graph, "gamze", "edip", 5);
    addEdge(graph, "gamze", "ferit", 5);
    addEdge(graph, "gamze", "halit", 5);
    addEdge(graph, "ferit", "cem", 6);
    addEdge(graph, "ferit", "dundar", 6);
    addEdge(graph, "ferit", "gamze", 6);
    addEdge(graph, "ferit", "halit", 6);
    addEdge(graph, "halit", "ferit", 7);
    addEdge(graph, "halit", "gamze", 7);
    addEdge(graph, "halit", "ilke", 7);
    addEdge(graph, "ilke", "halit", 8);
    addEdge(graph, "ilke", "jale", 8);
    addEdge(graph, "jale", "ilke", 9);

//    adjMatrix(graph);
//    printGraph(graph);
    centrality(graph);
    return 0;
}