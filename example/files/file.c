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
    struct Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    // Undirected graph
    newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;
}

// Function to perform BFS
void bfs(struct Node* adj[], int V, int s,
                             int visited[])
{
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[s] = 1; // Mark source as visited
    queue[rear++] = s; // Enqueue source

    while (front != rear) {
        int curr = queue[front++]; // Dequeue vertex
        printf("%d ", curr);

        // Get all adjacent vertices of curr
        struct Node* temp = adj[curr];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                visited[neighbor] = 1; // Mark as visited
                queue[rear++] = neighbor; // Enqueue it
            }
            temp = temp->next;
        }
    }
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

int main()
{
    int V = 6; // Number of vertices
    struct Node* adj[V];

    for (int i = 0; i < V; ++i) {
        adj[i] = NULL; // Initialize adjacency list
    }

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);

    // Perform BFS traversal for the entire graph
    bfsDisconnected(adj, V);

    return 0;
}
