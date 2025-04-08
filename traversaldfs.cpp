#include<iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    // Constructor to initialize a node with a value
    node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// Preorder traversal (non-member function)
void preorder(node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Inorder traversal (non-member function)
void inorder(node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Postorder traversal (non-member function)
void postorder(node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Function to insert a new node in the BST
node* insert(node* root, int value) {
    if (root == NULL) {
        return new node(value);  // Create a new node if root is NULL
    }
    if (value < root->data) {
        root->left = insert(root->left, value);  // Insert in the left subtree
    } else {
        root->right = insert(root->right, value);  // Insert in the right subtree
    }
    return root;
}

// Function to search for a node in the BST
node* search(node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Function to find the minimum value node (for deletion)
node* minValueNode(node* root) {
    node* temp = root;
    while (temp && temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

// Function to delete a node from the BST
node* deleteNode(node* root, int key) {
    if (root == NULL) {
        return root;
    }
 
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node to be deleted is found
        if (root->left == NULL && root->right == NULL) {
            delete root;  // Delete leaf node
            return NULL;
        } else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            // Node with two children
            node* temp = minValueNode(root->right);  // Get inorder successor
            root->data = temp->data;  // Copy the inorder successor's value
            root->right = deleteNode(root->right, temp->data);  // Delete the inorder successor
        }
    }
    return root;
}

int main() {
    node* root = NULL;  // Initialize root as NULL

    // Insert nodes into the BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Perform inorder traversal and print the result
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    // Perform preorder traversal
    cout << "Preorder traversal: ";
    preorder(root);
    cout << endl;

    // Perform postorder traversal
    cout << "Postorder traversal: ";
    postorder(root);
    cout << endl;

    // Search for a value
    int valueToSearch = 40;
    node* foundNode = search(root, valueToSearch);
    if (foundNode != NULL) {
        cout << "Node found with value: " << foundNode->data << endl;
    } else {
        cout << "Node not found." << endl;
    }

    // Delete a node
  
    root = deleteNode(root, 20);
    cout << "After deletion, Inorder traversal: ";
    inorder(root);
    cout << endl;

    return 0;
}

