#include<iostream>
#include<stack>
#include <vector>
//#include "Admin.h"
#include <iomanip>
#include<string>
//#include "Admin.h"

using namespace std;



vector<pair<int,int>> cart;
stack<int> finalProduct;


class Node{
    public:
    int id;
    int quantity;
    float price;
    string name;
    Node* next;
};
Node* head = NULL;

int productNo = 0;
//int placeOrder = 0;
void placeOrder(Node* &head);
int addToCart(Node* &head, int id, int q);
void viewCart(Node* &head);
int removeFromcart(int id);
void searchProduct(Node* &head, int id);
void showProducts(Node* &head);
//void product_list(Node* &head);
//void modify(Node* &head);






void table(Node* &temp){
    const char separator    = ' ';
    const int nameWidth     = 20;
    const int numWidth      = 20;

    cout << left << setw(nameWidth) << setfill(separator) << temp->id;
    cout << left << setw(nameWidth) << setfill(separator) << temp->name;
    cout << left << setw(numWidth) << setfill(separator) << temp->quantity;
    cout << left << setw(numWidth) << setfill(separator) << temp->price;
    cout << endl;

    //cin.get();
}

int addTocart(Node* &head, int id, int q){
    int choice;
    for (Node* temp = head; temp != NULL; temp = temp->next)
    {
        if (id==temp->id)
        {
            if(temp->quantity > 0){
                if (q <= temp->quantity)
                {
                cart.push_back(make_pair(id,q));
                ++productNo;
                
                cout<<"\n!!Products Addedd successfully In Cart :)!!\n";
                cout<<"\nEnter 1 to Go to cart or 0 to add more products: ";
                cin>>choice;
                if(choice == 1){
                    viewCart(head);
                    return 1;
                }
                else if (choice == 0){
                    int i, j;
                    cout<<"Product ID: ";
                    cin>>i;
                    cout<<"Quantity: ";
                    cin>>j;
                    addTocart(head, i, j);
                    return 1;
                }
                } else{
                    cout<<"\n!!Product Quantity Exceed!!\n";
                    cout<<"\nPlease Enter Product Quantity <= "<<temp->quantity<<endl;
                    cout<<"Enter Quantity or 0 to exit:\n";
                    cout<<"Quantity: ";
                    cin>>choice;
                    if (choice == 0)
                    {
                        return 1;
                    }
                    else{
                        q = choice;
                        addTocart(head,id,q);
                        return 0;
                        
                    }
                }
            } else cout<<temp->name<<" Out of Stock :(\n";

        } 
        
    }     
    return 0;
}


void showProducts(Node* &head){
    if(head==NULL){
        cout<<"!!No Products Found!!";
        return;
    }
    cout<<"================================================================="<<endl;
    cout<<"Product ID          Product Name        Quantity            Price"<<endl;
    cout<<"================================================================="<<endl;
    //string name;
    for(Node* temp=head; temp!=NULL; temp=temp->next){     
        table(temp);
    }
    cout<<"================================================================="<<endl; 
    int id,q;
    cout<<"\nEnter Products id to Add to cart or 0 to exit: ";
    cin>>id;
    
    if(id>0){
        cout<<"Enter Quantity: ";
        cin>>q;
        addTocart(head,id,q);
        return;
    }
    else if(id==0)
        return;
    else cout<<"\n!!Invalid Input!!\n";
    return;
    
}

void searchProduct(Node* &head, int id){
    cout<<"================================================================="<<endl;
    cout<<"Product ID          Product Name        Quantity            Price"<<endl;
    cout<<"================================================================="<<endl;
    for(Node* temp=head; temp!=NULL; temp=temp->next){
        if(id==temp->id){
            //cout<<temp->id<<"         "<<temp->name<<"         "<<temp->quantity<<"         "<<temp->price<<endl;
            table(temp);
            return;
        }
    }
    cout<<"!!Product Not available!!:(";

}



int removeFromcart(int id){
    for (int i = 0; i < cart.size(); i++)
    {
        if (id==cart[i].first)
        {
            while(i+1 < cart.size()){
                cart[i].first = cart[i+1].first;
                cart[i].second = cart[i+1].second;
                cart.pop_back();
                i++;
            }
            if(i+1 == cart.size())
                cart.pop_back();
            return 1;
        }
           
    }
    cout<<"!!Product Not available!!:(";
    return 0;
}

void viewCart(Node* &head){
    const char separator    = ' ';
    const int nameWidth     = 20;
    const int numWidth      = 20;

    cout<<"\n ==============================>"<<endl;
    cout<<" \\\\                 //===========>"<<endl;
    cout<<"  \\\\   C  A  R  T  //"<<endl;
    cout<<"   \\\\             //"<<endl;
    cout<<"    =============="<<endl;
    cout<<"    (+)        (+) "<<endl;
    cout<<"\n\n";


    if(head==NULL){
        cout<<"!!No Products Found!!:(\n";
        return;
    }
    cout<<"================================================================="<<endl;
    cout<<"Product ID          Product Name        Quantity            Price"<<endl;
    cout<<"================================================================="<<endl;
    for(int i=0; i < cart.size(); i++)
    for(Node* temp=head; temp!=NULL; temp=temp->next){
        if(temp->id==cart[i].first){
            cout << left << setw(nameWidth) << setfill(separator) << temp->id;
        cout << left << setw(nameWidth) << setfill(separator) << temp->name;
        cout << left << setw(numWidth) << setfill(separator) << cart[i].second;
        cout << left << setw(numWidth) << setfill(separator) << temp->price;
        cout << endl;
        }
    }
    cout<<"================================================================="<<endl;
    int choice;
    cout<<"Enter -1 to Place Order\n";
    cout<<"Enter Product id to remove products\n";
    cout<<"Enter 0 to exit\n";
    cin>>choice;
    if(choice == -1)
        placeOrder(head);
    else if(choice == 0)
        return;
    else for(int i=0; i < cart.size(); i++){
        if(choice == cart[i].first){
            removeFromcart(choice);
            viewCart(head);
        }
        else cout<<"\n!!Invalid Number Entered!!\n";
    }

}

void placeOrder(Node* &head){

    const char separator    = ' ';
    const int nameWidth     = 20;
    const int numWidth      = 20;


    if(head==NULL){
        cout<<"!!No Products Found!!:(\n";
        return;
    }
    if(cart.size()==0){
        cout<<"!!Cart is Empty!!:(\n";
        return;
    }
    int total = 0;
    cout<<"================================================================="<<endl;
    cout<<"Product ID          Product Name        Quantity            Price"<<endl;
    cout<<"================================================================="<<endl;
    for(int i=0; i < cart.size(); i++)
    for(Node* temp=head; temp!=NULL; temp=temp->next){
        if(temp->id==cart[i].first){
            cout << left << setw(nameWidth) << setfill(separator) << temp->id;
            cout << left << setw(nameWidth) << setfill(separator) << temp->name;
            cout << left << setw(numWidth) << setfill(separator) << cart[i].second;
            cout << left << setw(numWidth) << setfill(separator) << temp->price;
            cout << endl;
            total = total + temp->price*cart[i].second;
            //return;
        }
    }
    cout<<"================================================================="<<endl;
    cout<<"                                                      Total: "<<total<<endl;
    cout<<"================================================================="<<endl;
    int flag;
    cout<<"Press 1 to Order or 0 to cancel"<<endl;
    cin>>flag;
    if(flag==1){
        for(int i=0; i < cart.size(); i++)
        for(Node* temp=head; temp!=NULL; temp=temp->next){
            if(cart[i].first==temp->id){
                if(temp->quantity>0)
                    temp->quantity = temp->quantity-cart[i].second;
                else cout<<temp->name<<"Out of stock :(\n";
            }
        }
        cart.clear();
        cout<<"!!Order Placed Successfully!!:)";        
    }
    return;
}

// void product_list(Node* &head){
//     int id , quantity;
//     double price;
//     string name;

//     Node *new_node = new Node();
//     //t = ;
//     //Node *p=head;
//     if(head == NULL){
//         head=new_node;
//     } else{
//     Node* temp = head;
//     for (temp; temp->next !=NULL ; temp = temp->next);
//     temp->next = new_node;
//     new_node->next = NULL;
//     }

//     cout<<"\nEnter product ID :";
//     cin>>id;
//     new_node->id = id;
//     cout<<"Enter product Name :";
//     cin>>name;
//     new_node->name=name;
//     cout<<"Enter product quantity :";
//     cin>>quantity;
//     new_node->quantity=quantity;
//     cout<<"Enter product price :";
//     cin>>price;
//     new_node->price = price;
//     //head = t;
//     cout<<"\n\n=====================================================";
//     cout<<"\n\t\t!Product Addedd!\n";
//     cout<<"=====================================================\n"; 

//     return;
    

// }


   







