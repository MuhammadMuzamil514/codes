#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Task structure to hold the task name and its priority
struct Task {
    string name;
    int priority;
};

class MaxHeap {
private:
    vector<Task> heap;

    // Utility function to maintain heap property after insertion
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].priority > heap[parent].priority) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Utility function to maintain heap property after deletion
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left].priority > heap[largest].priority) {
                largest = left;
            }
            if (right < size && heap[right].priority > heap[largest].priority) {
                largest = right;
            }

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    // Insert a new task into the heap
    void insertHeap(const string& taskName, int priority) {
        if (heap.size() >= 20) {
            cout << "Heap is full. Cannot add more tasks.\n";
            return;
        }
        heap.push_back({taskName, priority});
        heapifyUp(heap.size() - 1);
    }

    // Delete the task with the highest priority
    void deleteMax() {
        if (heap.empty()) {
            cout << "Heap is empty. No tasks to complete.\n";
            return;
        }
        cout << "Completed task: " << heap[0].name << " with priority " << heap[0].priority << "\n";
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    // Display the current state of the heap
    void displayHeap() {
        if (heap.empty()) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Current Heap:\n";
        for (const auto& task : heap) {
            cout << "Task: " << task.name << ", Priority: " << task.priority << "\n";
        }
    }
};

int main() {
    MaxHeap taskScheduler;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add a task\n";
        cout << "2. Complete the highest-priority task\n";
        cout << "3. Display the heap\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string taskName;
                int priority;
                cout << "Enter task name: ";
                cin.ignore();
                getline(cin, taskName);
                cout << "Enter task priority: ";
                cin >> priority;
                taskScheduler.insertHeap(taskName, priority);
                taskScheduler.displayHeap();
                break;
            }
            case 2: {
                taskScheduler.deleteMax();
                taskScheduler.displayHeap();
                break;
            }
            case 3: {
                taskScheduler.displayHeap();
                break;
            }
            case 4: {
                cout << "Exiting program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 4);

    return 0;
}
