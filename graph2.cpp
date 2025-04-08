#include <bits/stdc++.h>
using namespace std;
class Graph{
    int V;
    list<int> *l;
    
  public:
  	Graph(int V){
  		this->V=V;
  		l=new list<int>[V];
	  }
  	
  	void addEdge(int u, int v){
  		l[u].push_back(v);
  		l[v].push_back(u);
	  }
void printGraph(){
		for(int i=0;i<V;i++){
			cout<<"Vertex "<<i<<" : ";
			for(int val:l[i]){
				cout<<val<<" ";
			}
			cout<<endl;
		}
	}
};

int main(){
	Graph g(4);
	g.addEdge(0,1);
	g.printGraph();
}

