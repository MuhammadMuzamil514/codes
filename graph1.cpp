#include <iostream>
using namespace std;
const int MAX_NODES = 6;
int arr[MAX_NODES][MAX_NODES];

/* function to initialize the matrix to zero */  
void init() {  
  int i, j;  
  for (i = 0; i < MAX_NODES; i++)  
    for (j = 0; j < MAX_NODES; j++)  
      arr[i][j] = 0;  
} 

/* function to add edges to the graph */  
void insertEdge(int i, int j) {  
  arr[i][j] = 1;  
  arr[j][i] = 1;  
}  
/* function to print the matrix elements */  
void printAdjMatrix() {  
  int i, j;  
  for (i = 0; i < MAX_NODES; i++) {  
    cout<<i<<": ";  
    for (j = 0; j < MAX_NODES; j++) {  
      cout<<arr[i][j]<<" ";  
    }  
    cout<<endl;  
  }  
} 
int main(){
	init();
	insertEdge(0,1);
	insertEdge(0,2);
	insertEdge(0,3);
	insertEdge(0,4);
	insertEdge(1,3);
	insertEdge(2,3);
	insertEdge(2,4);
	insertEdge(2,5);
	insertEdge(3,5);
	printAdjMatrix();
}

