#include <iostream>
#include <string>
using namespace std;

class MaxHeap {
private:
    string heap[20][2];  // 2D array: heap[i][0] stores task name, heap[i][1] stores priority
    int size;            // Current number of tasks in the heap
    int maxSize = 20;    // Maximum number of tasks allowed in the heap

    // Utility function to swap two elements in the heap
    void swap(int i, int j) {
        string tempName = heap[i][0];
        int tempPriority = stoi(heap[i][1]);

        heap[i][0] = heap[j][0];
        heap[i][1] = heap[j][1];

        heap[j][0] = tempName;
        heap[j][1] = to_string(tempPriority);
    }

    // Utility function to maintain the heap property by "heapifying" down from index i
    void heapify(int i) {
        int largest = i; 
        int left = 2 * i + 1;  // Left child
        int right = 2 * i + 2; // Right child

        // If left child is larger than root
        if (left < size && stoi(heap[left][1]) > stoi(heap[largest][1])) {
            largest = left;
        }

        // If right child is larger than the largest so far
        if (right < size && stoi(heap[right][1]) > stoi(heap[largest][1])) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            swap(i, largest);
            heapify(largest);  // Recursively heapify the affected subtree
        }
    }

    // Function to maintain the heap property by "heapifying" up from index i
    void heapifyUp(int i) {
        while (i > 0 && stoi(heap[(i - 1) / 2][1]) < stoi(heap[i][1])) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

public:
    MaxHeap() : size(0) {}

    // Insert a task into the heap
    void insertHeap(const string& taskName, int priority) {
        if (size >= maxSize) {
            cout << "Heap is full! Cannot insert new task." << endl;
            return;
        }

        heap[size][0] = taskName; // Store task name
        heap[size][1] = to_string(priority); // Store task priority as string
        size++;  // Increase the current size of the heap
        heapifyUp(size - 1);  // Restore heap property by heapifying up
    }

    // Delete the task with the highest priority (root of the heap)
    void deleteMax() {
        if (size == 0) {
            cout << "Heap is empty! No task to remove." << endl;
            return;
        }

        // Move the last element to the root and heapify
        heap[0][0] = heap[size - 1][0];
        heap[0][1] = heap[size - 1][1];
        size--;  // Decrease the size of the heap
        heapify(0);  // Restore the heap property by heapifying down
    }

    // Display the heap
    void displayHeap() {
        if (size == 0) {
            cout << "Heap is empty." << endl;
            return;
        }

        cout << "Current heap state:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Task: " << heap[i][0] << ", Priority: " << heap[i][1] << endl;
        }
        cout << endl;
    }
};

int main() {
    MaxHeap heap;
    int choice;
    string taskName;
    int priority;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. Complete the highest-priority task" << endl;
        cout << "3. Display the heap" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task name: ";
                cin.ignore(); // To clear the newline left by previous cin
                getline(cin, taskName);
                cout << "Enter task priority: ";
                cin >> priority;
                heap.insertHeap(taskName, priority);
                heap.displayHeap();
                break;
            case 2:
                heap.deleteMax();
                heap.displayHeap();
                break;
            case 3:
                heap.displayHeap();
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

