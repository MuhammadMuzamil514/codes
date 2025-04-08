#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Graph {
    int V;           // Number of vertices
    Node** adjList;  // Array of pointers to linked lists

public:
    // Constructor to initialize the graph
    Graph(int V) {
        this->V = V;
        adjList = new Node*[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = nullptr;
        }
    }

    // Function to add an undirected edge between two vertices
    void addEdge(int u, int v) {
        // Add v to u's list
        Node* newNode1 = new Node(v);
        newNode1->next = adjList[u];
        adjList[u] = newNode1;

        // Add u to v's list (since the graph is undirected)
        Node* newNode2 = new Node(u);
        newNode2->next = adjList[v];
        adjList[v] = newNode2;
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " : ";
            Node* temp = adjList[i];
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Destructor to free the memory
    ~Graph() {
        for (int i = 0; i < V; i++) {
            Node* temp = adjList[i];
            while (temp != nullptr) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
        }
        delete[] adjList;
    }
};

int main() {
    Graph g(4);  // Create a graph with 4 vertices
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.printGraph();  // Print the graph
    return 0;
}

