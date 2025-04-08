#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class CartNode {
public:
    int productId;
    string productName;
    double price;
    int quantity;
    CartNode *next;
    double discount;

   CartNode(int productId, const string& productName,double price,int quantity) {
    this->productId=productId;
    this->productName=productName;
    this->price=price;
    this->quantity=quantity;
    this->next=NULL;
    this->discount=0;
    applyDiscount();
}
    void applyDiscount() {
        if (quantity>10) {
            discount=0.15;
        } else if (quantity>5) {
            discount=0.10;
        } else {
            discount=0.0;
        }
    }

    double totalPrice() const {
        double total=price*quantity;
        total-=total*discount; 
        return total;
    }
};

class Cart {
private:
    CartNode*head;

public:
    Cart() {
    head=NULL;
}

    ~Cart() {
        while (head) {
            CartNode*temp=head;
            head=head->next;
            delete temp;
        }
    }
    void addItem(int productId,const string& productName,double price,int quantity) {
        CartNode* newNode=new CartNode(productId, productName, price, quantity);
        newNode->next=head;
        head=newNode;
    }

    void removeItem(int productId) {
        CartNode*current=head;
        CartNode*prev=NULL;

        while (current!=NULL&&current->productId!=productId) {
            prev=current;
            current=current->next;
        }

        if (current==NULL) {
            cout<<"Product not found in the cart." <<endl;
            return;
        }

        if (prev==NULL) {
            head=current->next;
        } else {
            prev->next=current->next;
        }
        delete current;
    }

    void displayCart() const {
        if (head==NULL) {
            cout<<"Your cart is empty."<<endl;
            return;
        }

        CartNode*current=head;
        double subtotal= 0;
        double discount= 0;

        cout<< "\nYour Cart:"<<endl;
        while (current!=NULL) {
            double itemTotal=current->totalPrice();
            if (current->discount>0) {
                double discountAmount=current->price*current->quantity*current->discount;
                discount+=discountAmount;
                itemTotal-=discountAmount;
                cout<<current->productName<<" x" <<current->quantity
                     << " - $" << itemTotal << " (Discount applied: -$" << discountAmount << ")" << endl;
            } else {
                cout << current->productName << " x" << current->quantity 
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
};

class QueueNode {
public:
    string request;  
    QueueNode* next; 
    QueueNode(const string& request) {
    this->request=request;
    this->next=NULL;
}
};

// Custom Queue class for handling checkout requests
class CustomQueue {
private:
    QueueNode*front;
    QueueNode*rear;

public:
    CustomQueue() {
    front=NULL;
    rear=NULL;
}

    ~CustomQueue() {
        while (front!=NULL) {
            QueueNode*temp=front;
            front=front->next;
            delete temp;
        }
    }
    void addRequest(const string& request) {
        QueueNode* newNode=new QueueNode(request);
        if (rear==NULL) {
            front=rear=newNode;
        } else {
            rear->next =newNode;
            rear=newNode;
        }
    }

    void processRequests() {
        while(front!=NULL) {
            cout << "Processing checkout for: " <<front->request <<endl;
            QueueNode* temp=front;
            front=front->next;
            delete temp;
        }
    }
};
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



class ProductNode {
public:
    int id;
    string name;
    double price;
    ProductNode* next;

   ProductNode(int id, const string& name, double price) {
    this->id = id;
    this->name = name;
    this->price = price;
    this->next = NULL;
}

};

class ProductCatalog {
private:
    ProductNode* head;

public:
   ProductCatalog() {
    head =NULL;
    loadProducts();
}


    ~ProductCatalog() {
        while (head != NULL) {
            ProductNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void loadProducts() {
        ifstream file("products.txt");
        if (file.is_open()) {
            int id;
            string name;
            double price;
            while (file >> id) {
                file.ignore(); 
                getline(file, name);
                file >> price;
                addProduct(id, name, price);
            }
            file.close();
        } else {
            cout << "No products file found. Creating a default catalog..." << endl;
            ofstream outfile("products.txt");
            if (outfile.is_open()) {
                outfile << "1\nApple\n0.99\n";
                outfile << "2\nBanana\n0.59\n";
                outfile << "3\nOrange\n1.29\n";
                outfile.close();

                addProduct(1, "Apple", 0.99);
                addProduct(2, "Banana", 0.59);
                addProduct(3, "Orange", 1.29);
            } else {
                cout << "Failed to create default products file!" << endl;
            }
        }
    }

    void addProduct(int id, const string& name, double price) {
        ProductNode* newNode = new ProductNode(id, name, price);
        newNode->next = head;
        head = newNode;
    }

    void removeProduct(int id) {
        ProductNode* current = head;
        ProductNode* prev = NULL;

        while (current != NULL && current->id != id) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << "Product not found." << endl;
            return;
        }

        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }

    void displayProducts() const {
        ProductNode* current = head;
        while (current != NULL) {
            cout << current->id << ". " << current->name << " - $" << current->price << endl;
            current = current->next;
        }
    }

    ProductNode* findProduct(int id) {
        ProductNode* current = head;
        while (current != NULL) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
};
class ActionHistory {
private:
    string* actions;  
    int capacity;      
    int size;        

    void resize() {
        capacity *= 2;  
        string* newActions = new string[capacity];
        for (int i = 0; i < size; ++i) {
            newActions[i] = actions[i];
        }
        delete[] actions;
        actions = newActions;
    }
public:
   
    ActionHistory() {
        capacity = 10;
        size = 0;
        actions = new string[capacity];
    }
    void pushAction(const string& action) {
        if (size == capacity) {
            resize();  
        }
        actions[size++] = action;
    }
    void undoAction() {
        if (size > 0) {
            cout << "Undo: " << actions[size - 1] << endl;
            --size;  
        } else {
            cout << "No actions to undo." << endl;
        }
    }
    ~ActionHistory() {
        delete[] actions;
    }
};

class User {
public:
    string username;
    string password;

  User(const string& username, const string& password) {
    this->username = username;
    this->password = password;
}

};

class UserNode {
public:
    string username;
    string password;
    UserNode* next;

    UserNode(const string& username, const string& password) {
    this->username = username;
    this->password = password;
    this->next = NULL;
}

};

class UserManager {
private:
    UserNode* head;

public:
    UserManager() {
    head =NULL;
    loadUsers();
}

    ~UserManager() {
        while (head != NULL) {
            UserNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void loadUsers() {
        ifstream file("users.txt");
        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {
                addUser(username, password);
            }
            file.close();
        } else {
            cout << "No users file found. Creating a default user..." << endl;
            addUser("user1", "password1");
            addUser("user2", "password2");
        }
    }

    void addUser(const string& username, const string& password) {
        UserNode* newNode = new UserNode(username, password);
        newNode->next = head;
        head = newNode;
    }
    bool login(const string& username, const string& password) {
        UserNode* current = head;
        while (current != NULL) {
            if (current->username == username && current->password == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};
class Administrator {
public:
    string username;
    string password;

    Administrator(const string& username, const string& password) {
        this->username = username; 
        this->password = password; 
    }
   Administrator() {
        username = ""; 
        password = ""; 
    }
};

class AdministratorManager {
private:
    class Node {
    public:
        Administrator admin;  
        Node* next; 

        Node(const Administrator& admin) {  
            this->admin = admin;  
            this->next = NULL;  
        }
    };

    Node* head;  
public:
    AdministratorManager() {
        head = NULL;
        loadAdministrators();
    }

    void loadAdministrators() {
        ifstream file("administrators.txt");
        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {
                addAdministrator(username, password);  
            }
            file.close();
        }
    }

    bool login(const string& username, const string& password) {
        Node* current = head;
        while (current != NULL) {
            if (current->admin.username == username && current->admin.password == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void addAdministrator(const string& username, const string& password) {
        Administrator newAdmin(username, password);  
        Node* newNode = new Node(newAdmin);  

        if (head == NULL) {
            head = newNode;
        } else {
         
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        ofstream file("administrators.txt", ios::app);  
        file << username << " " << password << endl; 
        file.close();
    }
    ~AdministratorManager() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};
int getValidIntInput() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(10000, '\n');  
            cout << "Invalid input! Please enter a valid integer: ";
        } else {
         
            cin.ignore(10000, '\n');  
            break;
        }
    }
    return choice;
}

double getValidDoubleInput() {
    double input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(10000, '\n');  
            cout << "Invalid input! Please enter a valid number: ";
        } else {
            cin.ignore(10000, '\n'); 
            break;
        }
    }
    return input;
}

int main() {
    UserManager userManager;
    ProductCatalog catalog;
    Cart cart;
    CustomQueue checkoutQueue;
    ActionHistory actionHistory;
    
    int loginChoice;
    bool loggedIn = false;
    bool isAdmin = false;
    int choice;

    while (true) {
    	cout << "\n=====================================" << endl;
    cout << "  * Shopping Cart Management System *" << endl;
    cout << "=====================================" << endl;
        cout << "Login as:" << endl;
        cout << "1. User" << endl;
        cout << "2. Administrator" << endl;
        cout << "Enter your choice: ";
        loginChoice = getValidIntInput();
        
        string username, password;
        
        if (loginChoice == 1) {
         
            cout << "\n1. Register New User" << endl;
            cout << "2. Login with Existing Account" << endl;
            cout << "Enter your choice: ";
            int userChoice = getValidIntInput();

            if (userChoice == 1) {
               
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                userManager.addUser(username, password);
                cout << "User registered successfully!\n";
                continue; 
            } else if (userChoice == 2) {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);

                if (userManager.login(username, password)) {
                    loggedIn = true;
                    isAdmin = false;
                    cout << "User logged in successfully!\n";
                } else {
                    cout << "Invalid login credentials!" <<endl;
                    continue; 
                }
            }
        } else if (loginChoice == 2) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            if (username == "admin" && password == "admin") {
                loggedIn = true;
                isAdmin = true;
                cout << "Administrator logged in successfully!\n";
            } else {
                cout << "Invalid login credentials!" << endl;
                continue;  
            }
        }

        while (loggedIn) {
            if (isAdmin) {
              
                cout << "\n[ Admin Menu ]" << endl;
    cout << "=========================" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. View Products" << endl;
    cout << "4. Logout" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
                choice = getValidIntInput();

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
                        catalog.addProduct(id, name, price);
                        cout<<"Product entered Successfully.";
                        
                        break;
                    }
                    case 2: {
                        int id;
                        cout << "Enter product ID to remove: ";
                        cin >> id;
                        catalog.removeProduct(id);
                         cout<<"Product removed Successfully.";
                          
                        break;
                    }
                    case 3:
                        catalog.displayProducts();
                        break;
                    case 4:
                        loggedIn = false;
                        cout << "Logged out successfully!" << endl;
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                }
            } else {
                cout << "\n[ User Menu ]" << endl;
    cout << "=========================" << endl;
    cout << "1. View Products" << endl;
    cout << "2. Add Product to Cart" << endl;
    cout << "3. Remove Product from Cart" << endl;
    cout << "4. View Cart" << endl;
    cout << "5. Undo Last Action" << endl;
    cout << "6. Checkout" << endl;
    cout << "7. Logout" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
                choice = getValidIntInput();

                switch (choice) {
                    case 1:
                        catalog.displayProducts();
                        break;
                    case 2: {
                        int id, quantity;
                        catalog.displayProducts();
                        cout << "Enter product ID: ";
                        cin >> id;
                        cout << "Enter quantity in(integer): ";
                        cin >> quantity;
                        ProductNode* product = catalog.findProduct(id);
                        if (product) {
                            cart.addItem(id, product->name, product->price, quantity);
                            actionHistory.pushAction("Added product to cart with ID " + to_string(id));
                        } else {
                            cout << "Product not found!" << endl;
                        }
                        break;
                    }
                    case 3: {
                        int id;
                        cout << "Enter product ID to remove: ";
                        cin >> id;
                        cart.removeItem(id);
                         actionHistory.pushAction("Removed product from cart with ID " + to_string(id));
                        break;
                    }
                    case 4:
                        cart.displayCart();
                        break;
                    case 5:
                        actionHistory.undoAction();
                        break;
                    case 6:
                        cout << "Proceeding to checkout..." << endl;
                        break;
                    case 7:
                        loggedIn = false;
                        cout << "Logged out successfully!" << endl;
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            }
        }
    }

    return 0;
}
