#include <iostream>
using namespace std;

// Define a custom Stack class
class Stack {
    char arr[100]; // Array to hold stack elements
    int topIndex;  

public:
    // Constructor to initialize the stack
    Stack() {
        topIndex = -1;
    }

    // Push function to add an element to the stack
    void push(char key) {
        if (topIndex < 99) {
            arr[++topIndex] = key;
        } else {
            cout << "Stack overflow! Cannot type more characters.\n";
        }
    }

    // Pop function to remove the top element
    void pop() {
        if (topIndex >= 0) {
            topIndex--;
        } else {
            cout << "Nothing to delete! The stack is empty.\n";
        }
    }

    // Top function to get the top element
    char top() {
        if (topIndex >= 0) {
            return arr[topIndex];
        } else {
            return '\0'; // Return null character if stack is empty
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return topIndex == -1;
    }

    // Reverse function to print reversed text
    void reverse() {
        if (isEmpty()) {
            cout << "No text to reverse.\n";
        } else {
            cout << "Reversed text: ";
            while (!isEmpty()) {
                cout << top();
                pop();
            }
            cout << endl;
        }
    }
};

// Main function
int main() {
    Stack keyboardStack;
    char choice;
    char key;

    cout << "Keyboard Simulation using Custom Stack\n";
    cout << "--------------------------------------\n";
    cout << "Commands:\n";
    cout << "1: Type a key (Push)\n";
    cout << "2: Press Backspace (Pop)\n";
    cout << "3: Reverse the text\n";
    cout << "4: Exit\n";

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == '1') {
            cout << "Enter a key to type: ";
            cin >> key;
            keyboardStack.push(key);
            cout << key << " has been typed.\n";
        } 
        else if (choice == '2') {
            cout << "Backspace pressed. Removing: " << keyboardStack.top() << endl;
            keyboardStack.pop();
        } 
        else if (choice == '3') {
            keyboardStack.reverse();
        } 
        else if (choice == '4') {
            cout << "Exiting the program.\n";
            break;
        } 
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

