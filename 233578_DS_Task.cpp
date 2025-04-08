#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Graph {
private:
    const int MAX_NODES = 5; 
    int arr[5][5]; 
    bool visited[5]; 

public:
    
    Graph() {
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                arr[i][j] = 0;
            }
            visited[i] = false;
        }
    }

  
    void insertEdge(int i, int j) {
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            arr[i][j] = 1;
            arr[j][i] = 1;
        } else {
            cout << "Invalid edge (" << i << "," << j << "). Vertex out of bounds!" << endl;
        }
    }
    void insertEdgeDirected(int i, int j) {
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            arr[i][j] = 1;
        } else {
            cout << "Invalid directed edge (" << i << "," << j << "). Vertex out of bounds!" << endl;
        }
    }

    void printAdjMatrix() {
        for (int i = 0; i < MAX_NODES; i++) {
            cout << i << ": ";
            for (int j = 0; j < MAX_NODES; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    void BFS(int start) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from vertex " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            // Check adjacent vertices
            for (int i = 0; i < MAX_NODES; i++) {
                if (arr[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    // Function to clear the visited array
    void clearVisited() {
        for (int i = 0; i < MAX_NODES; i++) {
            visited[i] = false;
        }
    }

    // Function to perform DFS traversal
    void DFS(int start) {
        stack<int> s;
        s.push(start);
        visited[start] = true;

        cout << "DFS traversal starting from vertex " << start << ": ";

        while (!s.empty()) {
            int node = s.top();
            s.pop();
            cout << node << " ";

            // Check adjacent vertices
            for (int i = 0; i < MAX_NODES; i++) {
                if (arr[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    s.push(i);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g;

    // Adding undirected edges
    g.insertEdge(0, 1);
    g.insertEdge(0, 2);
    g.insertEdge(0, 3);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 4);
    g.insertEdge(5, 3); 

    g.insertEdgeDirected(0, 1);
    g.insertEdgeDirected(1, 2);
    g.insertEdgeDirected(2, 3);

    // Print adjacency matrix
    g.printAdjMatrix();
    g.BFS(0);
    g.clearVisited();
    g.DFS(0);

    return 0;
}
