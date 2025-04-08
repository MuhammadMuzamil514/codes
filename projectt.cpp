#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

struct Item {
    int itemID;
    string name;
    float price;
    int quantity;
};

class ShoppingCart {
    vector<Item> cart;
    unordered_map<int, Item> inventory;

public:
    void addItemToInventory(int id, string name, float price, int quantity) {
        Item newItem = {id, name, price, quantity};
        inventory[id] = newItem;
    }

    void addItemToCart(int itemID, int quantity) {
        if (inventory.find(itemID) != inventory.end()) {
            Item item = inventory[itemID];
            item.quantity = quantity;
            cart.push_back(item);
        } else {
            cout << "Item not found in inventory!" << endl;
        }
    }

    void removeItemFromCart(int itemID) {
        for (auto it = cart.begin(); it != cart.end(); ++it) {
            if (it->itemID == itemID) {
                cart.erase(it);
                break;
            }
        }
    }

    void viewCart() {
        float total = 0;
        for (auto &item : cart) {
            cout << "ID: " << item.itemID << ", Name: " << item.name << ", Quantity: " 
                 << item.quantity << ", Price: $" << item.price << endl;
            total += item.price * item.quantity;
        }
        cout << "Total: $" << total << endl;
    }

    void checkout() {
        float total = 0;
        for (auto &item : cart) {
            total += item.price * item.quantity;
        }
        cout << "Total: $" << total << endl;
        // Process payment and clear the cart
        cart.clear();
    }
};

int main() {
    ShoppingCart cart;
    cart.addItemToInventory(1, "Apple", 1.2, 100);
    cart.addItemToInventory(2, "Banana", 0.8, 150);
    
    cart.addItemToCart(1, 2);
    cart.addItemToCart(2, 3);

    cart.viewCart();
    cart.checkout();

    return 0;
}

