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

// Function to add an edge to the graph
void addEdge(struct Node* adj[], int u, int v)
{
    struct Node* n = createNode(v);
    n->next = adj[u];
    adj[u] = n;

    // Undirected graph
    n = createNode(v);
    n->next = adj[u];
    adj[u] = n;
}


// Function to perform BFS for the entire graph
void bfsDisconnected(struct Node* adj[], int V)
{
    // Mark all vertices as not visited
    int v[V];
    for (int i = 0; i < V; i++) {
        v[i] = 0;
    }

    for (int i = 0; i < V; ++i) {
        if (!v[i]) {
            bfs(adj, V, i, v);
        }
    }
}

int main()
{
    int V = 6; // Number of vertices
    struct Node* a[V];

    for (int i = 0; i < V; ++i) {
        a[i] = NULL; // Initialize adjacency list
    }

    // Add edges to the graph
    addEdge(a, 0, 1);
    addEdge(a, 0, 2);
    addEdge(a, 3, 4);
    addEdge(a, 4, 5);

    // Perform BFS traversal for the entire graph
    bfsDisconnected(a, V);

    return 0;
}
