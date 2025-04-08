#include <iostream>
using namespace std;
class Graph {
private:
    int MAX_NODES; 
    int **arr;       
    bool *visited;  

public:
    Graph(int nodes) {
        MAX_NODES = nodes;
        
        arr = new int*[MAX_NODES];
        for (int i = 0; i < MAX_NODES; ++i) {
            arr[i] = new int[MAX_NODES]();
        }
        visited = new bool[MAX_NODES]();
    }

    // Function to insert an undirected edge
    void insertEdge(int i, int j) {
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            arr[i][j] = 1;
            arr[j][i] = 1; 
        } else {
            cout << "Invalid edge (" << i << "," << j << "). Vertex out of bounds!" << endl;
        }
    }
    // Function to insert a directed edge
    void insertEdgeDirected(int i, int j) {
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            arr[i][j] = 1;
        } else {
            cout << "Invalid directed edge (" << i << "," << j << "). Vertex out of bounds!" << endl;
        }
    }

    // Function to remove an undirected edge
    void removeEdge(int i, int j) {
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            arr[i][j] = 0;
            arr[j][i] = 0; 
        } else {
            cout << "Invalid edge (" << i << "," << j << "). Vertex out of bounds!" << endl;
        }
    }

    // Function to print the adjacency matrix
    void printAdjMatrix() {
        for (int i = 0; i < MAX_NODES; i++) {
            cout << i << ": ";
            for (int j = 0; j < MAX_NODES; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    // Function to perform BFS traversal
    void BFS(int start) {
        int *queue = new int[MAX_NODES];
        int front = 0, rear = 0;
        visited[start] = true;
        queue[rear++] = start;
        cout << "BFS traversal starting from vertex " << start << ": ";

        while (front < rear) {
            int node = queue[front++];
            cout << node << " ";

            // Check adjacent vertices
            for (int i = 0; i < MAX_NODES; i++) {
                if (arr[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    queue[rear++] = i;
                }
            }
        }
        cout << endl;
        delete[] queue;
    }
    void clearVisited() {
        for (int i = 0; i < MAX_NODES; i++) {
            visited[i] = false;
        }
    }
    void DFS(int start) {
        int *stack = new int[MAX_NODES];
        int top = -1;

        stack[++top] = start;
        visited[start] = true;

        cout << "DFS traversal starting from vertex " << start << ": ";

        while (top >= 0) {
            int node = stack[top--];
            cout << node << " ";
            for (int i = 0; i < MAX_NODES; i++) {
                if (arr[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    stack[++top] = i;
                }
            }
        }
        cout << endl;
        delete[] stack;
    }

    ~Graph() {
        // Free the adjacency matrix
        for (int i = 0; i < MAX_NODES; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] visited;
    }
};
int main() {
    int nodes = 5;
    Graph g(nodes);
     g.insertEdge(5, 3);
 
    g.insertEdge(0, 1);
    g.insertEdge(0, 2);
    g.insertEdge(0, 3);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 4);

    g.insertEdgeDirected(0, 1);
    g.insertEdgeDirected(1, 2);
    g.insertEdgeDirected(2, 3);

    cout << "Adjacency Matrix:" << endl;
    g.printAdjMatrix();

    g.clearVisited();  
    g.BFS(0);

    
    g.clearVisited();
    g.DFS(0);

    return 0;
}

