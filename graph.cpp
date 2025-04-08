#include <iostream>
#include <string>
using namespace std;

#define SIZE 20  

class Task {
public:
    string name;
    int priority;

    Task() {
        name = "";
        priority = 0;
    } 

    Task(string taskName, int taskPriority) {
        name = taskName;
        priority = taskPriority;
    }
};

class TaskScheduler {
    Task arr[SIZE];
    int heapSize;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left_child(int i) {
        return (2 * i) + 1;
    }

    int right_child(int i) {
        return (2 * i) + 2;
    }

    void heapifyUp(int i) {
        if (i != 0) {
            int p = parent(i);
            if (arr[p].priority < arr[i].priority) {
                swap(arr[p], arr[i]);
                heapifyUp(p);
            }
        }
    }

    void heapifyDown(int i) {
        int l = left_child(i);
        int r = right_child(i);
        int largest = i;

        if (l < heapSize && arr[l].priority > arr[largest].priority)
            largest = l;
        if (r < heapSize && arr[r].priority > arr[largest].priority)
            largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyDown(largest);
        }
    }

public:
    TaskScheduler() {
        heapSize = 0;
    }

    void insertHeap(string taskName, int priority) {
        if (heapSize == SIZE) {
            cout << "Heap Overflow\n";
            return;
        }
        int i = heapSize;
        arr[i].name = taskName;
        arr[i].priority = priority;
        heapSize++;
        heapifyUp(i);
    }

    void deleteMax() {
        if (heapSize == 0) {
            cout << "Heap Underflow\n";
            return;
        }
        cout << "Completed task: " << arr[0].name << " with priority " << arr[0].priority << endl;
        heapSize--;
        arr[0] = arr[heapSize];
        heapifyDown(0);
    }

    void displayHeap() {
        if (heapSize == 0) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Current tasks in the heap:\n";
        for (int i = 0; i < heapSize; i++) {
            cout << "Task: " << arr[i].name << ", Priority: " << arr[i].priority << endl;
        }
        cout << endl;
    }

    void menu() {
        int choice;
        string taskName;
        int priority;

        while (true) {
            cout << "Task Scheduling System\n";
            cout << "1. Add a task\n";
            cout << "2. Complete the highest-priority task\n";
            cout << "3. Display the heap\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter task name: ";
                    cin.ignore();
                    getline(cin, taskName);
                    cout << "Enter task priority (higher number means higher priority): ";
                    cin >> priority;
                    insertHeap(taskName, priority);
                    displayHeap();
                    break;
                case 2:
                    deleteMax();
                    displayHeap();
                    break;
                case 3:
                    displayHeap();
                    break;
                case 4:
                    cout << "Exiting system.\n";
                    return;
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        }
    }
};

int main() {
    TaskScheduler scheduler;
    scheduler.menu();
    
}
