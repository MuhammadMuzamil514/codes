#include <iostream>
using namespace std;

// Class representing a graph
class Graph {
private:
    int V; // Number of vertices
    int adj[10][10]; // Adjacency matrix (for simplicity, assuming maximum 10 vertices)

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        // Initialize the adjacency matrix with 0
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
        }
    }

    // Add an edge to the graph (undirected)
    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Remove this line for a directed graph
    }

    // BFS (Breadth-First Search) using an array to mimic a queue
    void BFS(int start) {
        bool visited[10] = {false};  // To track visited vertices
        int q[10];  // Array to mimic the queue
        int front = 0, rear = 0;

        visited[start] = true;
        q[rear++] = start; // Enqueue the start vertex

        cout << "BFS starting from vertex " << start << ": ";

        while (front < rear) {
            int node = q[front++];  // Dequeue the front element
            cout << node << " ";

            // Visit all the neighbors
            for (int i = 0; i < V; i++) {
                if (adj[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q[rear++] = i;  // Enqueue the neighbor
                }
            }
        }
        cout << endl;
    }

    // DFS (Depth-First Search) using an array to mimic a stack
    void DFS(int start) {
        bool visited[10] = {false};  // To track visited vertices
        int s[10];  // Array to mimic the stack
        int top = -1;

        visited[start] = true;
        s[++top] = start;  // Push start vertex into stack

        cout << "DFS starting from vertex " << start << ": ";

        while (top >= 0) {
            int node = s[top--];  // Pop the top element
            cout << node << " ";

            // Visit all the neighbors
            for (int i = 0; i < V; i++) {
                if (adj[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    s[++top] = i;  // Push the neighbor to stack
                }
            }
        }
        cout << endl;
    }

    // Recursive DFS (Alternative)
    void DFSRecursive(int start) {
        bool visited[10] = {false};  // To track visited vertices
        cout << "DFS (Recursive) starting from vertex " << start << ": ";
        DFSRecursiveUtil(start, visited);
        cout << endl;
    }

    void DFSRecursiveUtil(int node, bool visited[10]) {
        visited[node] = true;
        cout << node << " ";

        // Visit all the neighbors recursively
        for (int i = 0; i < V; i++) {
            if (adj[node][i] == 1 && !visited[i]) {
                DFSRecursiveUtil(i, visited);
            }
        }
    }
};

int main() {
    // Create a graph with 6 vertices
    Graph g(6);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Perform BFS starting from vertex 0
    g.BFS(0);

    // Perform DFS (Iterative) starting from vertex 0
    g.DFS(0);

    // Perform DFS (Recursive) starting from vertex 0
    g.DFSRecursive(0);

    return 0;
}

