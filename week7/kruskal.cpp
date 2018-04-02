/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 20Feb, 2018
  Problem: Kruskal's Algorithm Implementation
*/

#include<iostream>
#include "priority_queue.h"
#include "linked_list.h"
using namespace std;


//Node information in Priority Queue
class item{
public:
      int i;
      int j;
      int key;          //weight of edge
};

//edge information
class edge{
public:
      int dest;    //destination vertex
      int wt;     //edge weight
};

//Each Vertex and its adjacent list information
template<class T>   //T = edge
class graphNode{
public:
      dll<T> adjList;   //adjacency list
      bool visited = false;
      int parent = -1;       //to store parent
      int Rank ;
};

template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
class Graph{
public:
      int V;
      int E;
      T1* vertex;

      Graph(int n, int m){
            V = n;
            E = m;
            vertex = new T1[V];
      }

      void add_edge(int a, int b, int wt);
      void print();
      void kruskal();
      void make_set();
      void union1(int u, int v);
      int find(int u);
};

template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::add_edge(int a, int b, int wt){
      vertex[a].adjList.push_back({b, wt});
}

//Print vertex and its adjacent list
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::print(){
      cout<<"-----Graph---------\n";
      for(int i =0; i<V; i++){
            cout<<i<<": ";
            for(class dll<T2>::iterator itr= vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  cout<<(*itr).dest<<','<<(*itr).wt<<"  ";
            }
            cout<<endl;
      }
      cout<<"---------------------\n";
}

//find mst
template<class T1, class T2>
void Graph<T1, T2>::kruskal(){
      item *arr = new item[E];
      int ind = 0;
      for(int i =0; i<V; i++){
            for(class dll<T2>::iterator itr= vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  arr[ind] = {i, (*itr).dest, (*itr).wt};
                  ind++;
            }
      }
      queue_priority<item> pq = build_heap(arr, E, V+1);
      list<item> mst;
      make_set();
      int tot_wt= 0;

      while(mst.size()!=V-1){
            item tmp = pq.pop();
            if(find(tmp.i)!=find(tmp.j)){
                  union1(tmp.i, tmp.j);
                  mst.push_back({tmp.i, tmp.j, tmp.key});
                  cout<<"("<<tmp.i<<"--"<<tmp.j<<", "<<tmp.key<<")\n";
                  tot_wt+=tmp.key;
            }
      }
      cout<<"Total Weight: "<<tot_wt<<endl;
}

//find root of a vertex
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
int Graph<T1, T2>::find(int u){
      if(vertex[u].parent == u) return u;
      vertex[u].parent = find(vertex[u].parent);
      return vertex[u].parent;
}

//union of two disjoint set
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::union1(int u, int v){
      int x = find(u);
      int y = find(v);
      if(x!=y){
            if(vertex[x].Rank == vertex[y].Rank){
                  vertex[x].parent = y;
                  vertex[y].Rank+=1;
            }
            else if(vertex[x].Rank < vertex[y].Rank){
                  vertex[x].parent = y;
            }
            else{
                  vertex[y].parent = x;
            }
      }
}

//intialize parent and rank of each element
template<class T1, class T2>
void Graph<T1, T2>::make_set(){
      for(int i =0; i<V; i++){
            vertex[i].parent = i;
            vertex[i].Rank = 0;
      }
}

int main(){
      int n,m;   //no. of vertex and no. of edge
      cin>>n>>m;
      Graph<graphNode<edge>, edge> G(n, m);
      int a, b, wt;
      for(int i =0; i<m; i++){
            cin>>a>>b>>wt;
            G.add_edge(a, b, wt);
      }
      G.print();
      G.kruskal();
}
