#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class  QueueNode {
	public:
    string request;  // Data to store
    QueueNode* next; // Pointer to the next node

    QueueNode(const string& request) : request(request), next(NULL) {}
};
// Custom Queue class
class CustomQueue {
private:
    QueueNode* front; // Pointer to the front of the queue
    QueueNode* rear;  // Pointer to the rear of the queue

public:
    // Constructor
    CustomQueue() : front(NULL), rear(NULL) {}

    // Destructor to clean up memory
    ~CustomQueue() {
        while (front != NULL) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Function to add a request to the queue (enqueue)
    void addRequest(const string& request) {
        QueueNode* newNode = new QueueNode(request);
        if (rear == NULL) {
            // If the queue is empty, both front and rear will point to the new node
            front = rear = newNode;
        } else {
            // Add the new node to the rear and update the rear pointer
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Function to process (dequeue) the front request
    void processRequests() {
        if (front == NULL) {
            cout << "No requests to process." << endl;
            return;
        }

        // Process the front request
        while (front != NULL) {
            cout << "Processing checkout for: " << front->request << endl;
            QueueNode* temp = front;
            front = front->next;
            delete temp; // Deallocate memory
        }

        // After processing all requests, reset the rear pointer
        rear = NULL;
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return front == NULL;
    }
};

// Class representing an item/product
class Product {
public:
    int id;
    string name;
    double price;
    

    Product(int id, const string& name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }

    void display() const {
        cout << id << ". " << name << " - $" << price << endl;
    }
    bool isNameEqual(const string& searchName) const {
        return name == searchName;
    }

    bool isIdEqual(int searchId) const {
        return id == searchId;
    }
};

// Node for linked list used for shopping cart entries
class CartNode {
public:
    Product product;
    int quantity;
    CartNode* next;
    double discount;  // Discount applied based on quantity

    CartNode(Product product, int quantity) : product(product), quantity(quantity), next(NULL), discount(0) {}

    // Function to calculate the total price after applying the discount
    double totalPrice() const {
        double price = product.price * quantity;
        price -= price * discount;  // Apply discount
        return price;
    }

    // Function to apply discount based on quantity
    void applyDiscount() {
        if (quantity > 10) {
            discount = 0.15; // 15% discount for more than 10 items
        } else if (quantity > 5) {
            discount = 0.10; // 10% discount for more than 5 items
        } else {
            discount = 0.0;  // No discount for 5 or fewer items
        }
    }
};

// Linked List for Cart Management
class Cart {
private:
    CartNode* head;

public:
    Cart() : head(NULL) { }

    ~Cart() { // Destructor to clean up cart nodes
        while (head) {
            CartNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

   void addItem(Product product, int quantity) {
        CartNode* newNode = new CartNode(product, quantity);
        newNode->applyDiscount();
        newNode->next = head;
        head = newNode;
    }


    void removeItem(int productId) {
        CartNode* current = head;
        CartNode* prev = NULL;

        while (current != NULL && current->product.id != productId) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << "Product not found in the cart." << endl;
            return;
        }

        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }


    void displayCart() const {
        if (head == NULL) {
            cout << "Your cart is empty." << endl;
            return;
        }

        CartNode* current = head;
        double subtotal = 0;
        double discount = 0;

        cout << "\nYour Cart:" << endl;
        while (current != NULL) {
            double itemTotal = current->totalPrice();
            if (current->discount > 0) {
                double discountAmount = current->product.price * current->quantity * current->discount;
                discount += discountAmount;
                itemTotal -= discountAmount;
                cout << current->product.name << " x" << current->quantity 
                     << " - $" << itemTotal << " (Discount applied: -$" << discountAmount << ")" << endl;
            } else {
                cout << current->product.name << " x" << current->quantity 
                     << " - $" << itemTotal << endl;
            }

            subtotal += itemTotal;
            current = current->next;
        }

        cout << "\nSubtotal: $" << subtotal << endl;
        double tax = subtotal * 0.1; 
        double total = subtotal + tax;
        cout << "Tax: $" << tax << endl;
        cout << "Final Total: $" << total - discount << endl;
    }

    CartNode* getHead() const {
        return head;
    }

    void clear() {
        while (head) {
            CartNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


// Action history class
class ActionHistory {
private:
    vector<string> actions;

public:
    void pushAction(const string& action) {
        actions.push_back(action);
    }

    void undoAction() {
        if (!actions.empty()) {
            cout << "Undo: " << actions.back() << endl;
            actions.pop_back();
        } else {
            cout << "No actions to undo." << endl;
        }
    }
};

// Class for managing product catalog
class ProductCatalog {
private:
    vector<Product> products;

public:
    ProductCatalog() {
        loadProducts();
    }

    // Load products from file or create default file if missing
void loadProducts() {
    ifstream file("products.txt");
    if (file.is_open()) {
        int id;
        string name;
        double price;
        while (file >> id) {
            file.ignore(); // Clear newline character
            getline(file, name);
            file >> price;
            products.emplace_back(id, name, price);
        }
        file.close();
    } else {
        // File doesn't exist, create it with default data
        cout << "No products file found. Creating a default catalog..." << endl;
        ofstream outfile("products.txt");
        if (outfile.is_open()) {
            // Default product data
            outfile << "1\nApple\n0.99\n";
            outfile << "2\nBanana\n0.59\n";
            outfile << "3\nOrange\n1.29\n";
            outfile.close();

            // Load default data into the program
            products.emplace_back(1, "Apple", 0.99);
            products.emplace_back(2, "Banana", 0.59);
            products.emplace_back(3, "Orange", 1.29);
        } else {
            cout << "Failed to create default products file!" << endl;
        }
    }
}




    void saveProducts() {
        ofstream file("products.txt");
        if (file.is_open()) {
            for (const auto& product : products) {
                file << product.id << "\n" << product.name << "\n" << product.price << endl;
            }
            file.close();
        }
    }

    void displayProducts() const {
        cout << "\nAvailable Products:" << endl;
        for (const auto& product : products) {
            product.display();
        }
    }
Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.id == id) {
                return &product;
            }
        }
        cout << "Product with ID " << id << " not found!" << endl;
        return NULL;
    }
   
   void addProduct(const Product& product) {
    // Validate ID and price before proceeding
    if (product.id < 0 || product.price < 0) {
        cout << "Product ID and price must be positive values." << endl;
        return; // Exit the function early to avoid adding invalid products
    }

    // Check if product ID already exists
    for (const auto& p : products) {
        if (p.id == product.id) {
            cout << "Product with that ID already exists." << endl;
            return;
        }
    }

    // Add the product to the list
    products.push_back(product);
    saveProducts(); // Save the updated list of products
    
    return;
}


    void removeProduct(int productId) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->id == productId) {
                products.erase(it);
                cout << "Product removed successfully." << endl;
                saveProducts(); // Save changes automatically
                return;
            }
        }
        cout << "Product not found." << endl;
    }
};

// User Management
class User {
public:
    string username;
    string password;

    User(const string& username, const string& password) {
        this->username = username;
        this->password = password;
    }
};

class UserManager {
private:
    vector<User> users;

public:
    UserManager() {
        loadUsers();
    }

    // Load users from file or create default file if missing
void loadUsers() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password;
        while (file >> username >> password) {
            users.emplace_back(username, password);
        }
        file.close();
    } else {
        // File doesn't exist, create it with default data
        cout << "No users file found. Creating a default user list..." << endl;
        ofstream outfile("users.txt");
        if (outfile.is_open()) {
            // Default user data
            outfile << "user1 password1\n";
            outfile << "user2 password2\n";
            outfile.close();

            // Load default data into the program
            users.emplace_back("user1", "password1");
            users.emplace_back("user2", "password2");
        } else {
            cout << "Failed to create default users file!" << endl;
        }
    }
}
    void saveUsers() {
        ofstream file("users.txt");
        if (file.is_open()) {
            for (const User& user : users) {
                file << user.username << " " << user.password << endl;
            }
            file.close();
        }
    }
 
    bool login(const string& username, const string& password) {
        for (const User& user : users) {
            if (user.username == username && user.password == password) {
                return true;
            }
        }
        return false;
    }

    void addUser(const string& username, const string& password) {
        users.emplace_back(username, password);
        saveUsers();
    }
    // Add this method to the UserManager class
void registerUser(const string& username, const string& password) {
    // Check if the username already exists
    for (const User& user : users) {
        if (user.username == username) {
            cout << "Username already exists! Please choose a different one." << endl;
            return;
        }
    }

    // Add the new user to the list
    users.emplace_back(username, password);
    saveUsers();  // Save updated users list to file
    cout << "User registered successfully!" << endl;
}

};

// Administrator Management
class Administrator {
public:
    string username;
    string password;

    Administrator(const string& username, const string& password) {
        this->username = username;
        this->password = password;
    }
};

class AdministratorManager {
private:
    vector<Administrator> administrators;

public:
    AdministratorManager() {
        loadAdministrators();
    }

    void loadAdministrators() {
        ifstream file("administrators.txt");
        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {
                administrators.emplace_back(username, password);
            }
            file.close();
        } else {
            cout << "No administrators file found, starting with an empty admin list." << endl;
        }
    }

    void saveAdministrators() {
        ofstream file("administrators.txt");
        if (file.is_open()) {
            for (const Administrator& administrator : administrators) {
                file << administrator.username << " " << administrator.password << endl;
            }
            file.close();
        }
    }

    bool login(const string& username, const string& password) {
        for (const Administrator& administrator : administrators) {
            if (administrator.username == username && administrator.password == password) {
                return true;
            }
        }
        return false;
    }

    void addAdministrator(const string& username, const string& password) {
        administrators.emplace_back(username, password);
        saveAdministrators();
    }
};

// Queue for checkout requests
class CheckoutQueue {
private:
    queue<string> checkoutRequests;

public:
    void addRequest(const string& request) {
        checkoutRequests.push(request);
    }

    void processRequests() {
        while (!checkoutRequests.empty()) {
            cout << "Processing checkout for: " << checkoutRequests.front() << endl;
            checkoutRequests.pop();
        }
    }
};

// Main Menu Functions
void showUserMenu() {
    cout << "\n[ User Menu ]" << endl;
    cout << "1. View Products" << endl;
    cout << "2. Add Product to Cart" << endl;
    cout << "3. Remove Product from Cart" << endl;
    cout << "4. View Cart" << endl;
    cout << "5. Undo Last Action" << endl;
    cout << "6. Checkout" << endl;
    cout << "7. Logout" << endl;
    cout << "Enter your choice: ";
}

void showAdminMenu() {
    cout << "\n[ Admin Menu ]" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. View Products" << endl;
    cout << "4. Logout" << endl;
    cout << "Enter your choice: ";
}

int main() {
    UserManager userManager;
    AdministratorManager administratorManager;
    ProductCatalog catalog;
    Cart cart;
    ActionHistory actionHistory;
    CheckoutQueue checkoutQueue;
    bool loggedIn = false;
    bool isAdmin = false;

    while (true) {
        int loginChoice;

        // Loop until valid login or register choice
        while (true) {
            cout << "Login as:" << endl;
            cout << "1. User" << endl;
            cout << "2. Administrator" << endl;
            cout << "3. Register (for new users)" << endl; // Add this option for registration
            cout << "Enter your choice: ";
            cin >> loginChoice;

            // Clear newline character after reading the login choice
            cin.ignore();

            if (loginChoice == 3) {  // Registration choice
                string username, password;
                cout << "Enter new username: ";
                getline(cin, username); // Use getline to handle spaces in username
                cout << "Enter new password: ";
                getline(cin, password); // Use getline for passwords as well

                userManager.registerUser(username, password); // Register new user
                continue;  // Continue back to the login options after registration
            }

            string username, password;
            cout << "Enter username: ";
            getline(cin, username); // Use getline to handle spaces in username
            cout << "Enter password: ";
            getline(cin, password); // Use getline for passwords as well

            if (loginChoice == 1 && userManager.login(username, password)) {
                cout << "User login successful!" << endl;
                loggedIn = true;
                isAdmin = false;
                break; // Valid login for user; exit loop
            } else if (loginChoice == 2 && administratorManager.login(username, password)) {
                cout << "Administrator login successful!" << endl;
                loggedIn = true;
                isAdmin = true;
                break; // Valid login for admin; exit loop
            } else {
                cout << "Invalid login credentials!" << endl; // Show error message and prompt again
            }
        }

        while (loggedIn) {
            if (isAdmin) {
                showAdminMenu();
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1: {
                        int id;
                        string name;
                        double price;
                        cout << "Enter product ID: ";
                        cin >> id;
                        cout << "Enter product name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter product price: ";
                        cin >> price;
                         
                        catalog.addProduct(Product(id, name, price));
                        cout << "Product added successfully!" << endl;
                            break;
                        }
             
                    case 2: {
                        int id;
                        cout << "Enter product ID to remove: ";
                        cin >> id;
                        catalog.removeProduct(id);
                        break;
                    }
                    case 3: {
                        catalog.displayProducts();
                        break;
                    }
                    case 4: {
                        cout << "Logging out...\n";
                        loggedIn = false;
                        break;
                    }
                    default: {
                        cout << "Invalid choice, please try again." << endl;
                        break;
                    }
                }
            } else {
                showUserMenu();
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1: {
                        catalog.displayProducts();
                        break;
                    }
                    case 2: {
                        int productId, quantity;
                        cout << "Enter product ID to add to cart: ";
                        cin >> productId;
                        cout << "Enter quantity: ";
                        cin >> quantity;

                        if (quantity <= 0) {
                            cout << "Quantity must be a positive number." << endl;
                            break;
                        }

                        Product* product = catalog.findProduct(productId);
                        if (product != NULL) {
                            cart.addItem(*product, quantity);
                            stringstream ss;
                            ss << "Added " << product->name << " x" << quantity;
                            actionHistory.pushAction(ss.str());
                            cout << "Added to cart!" << endl;
                        } else {
                            cout << "Product not found!" << endl;
                        }
                        break;
                    }
                    case 3: {
                        int productId;
                        cout << "Enter product ID to remove from cart: ";
                        cin >> productId;

                        cart.removeItem(productId);
                        stringstream ss;
                        ss << "Removed product with ID " << productId;
                        actionHistory.pushAction(ss.str());
                        break;
                    }
                    case 4: {
                        cart.displayCart();
                        break;
                    }
                    case 5: {
                        actionHistory.undoAction();
                        break;
                    }
                    case 6: {
                        cout << "\nProceeding to checkout...\n";
                        CartNode* current = cart.getHead(); // Use the public getter for the head of the cart
                        while (current != NULL) {
                            string request = "Product: " + current->product.name + " x" + to_string(current->quantity);
                            checkoutQueue.addRequest(request); // Add to checkout queue
                            current = current->next; // Move to next cart item
                        }
                        checkoutQueue.processRequests(); // Process the checkout queue
                        loggedIn = false; // Log out after checkout
                        break;
                    }
                    case 7: {
                        cout << "Logging out...\n";
                        loggedIn = false;
                        break;
                    }
                    default: {
                        cout << "Invalid choice, please try again." << endl;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

