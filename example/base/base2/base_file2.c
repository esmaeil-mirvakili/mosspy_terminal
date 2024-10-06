#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data)
{
    struct Node* newNode =
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to perform BFS for the entire graph
void bfsDisconnected(struct Node* adj[], int V)
{
    // Mark all vertices as not visited
    int visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            bfs(adj, V, i, visited);
        }
    }
}