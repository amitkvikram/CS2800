/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 30Jan, 2018
  Problem: Dijkstra Implementation
*/

#include <iostream>
#include "linked_list.h"
#include "priority_queue.h"
using namespace std;

//edge information
class edge{
public:
      int ind;    //destination vertex
      int wt;     //edge weight
};

template<class T>   //T = edge
class graphNode{
public:
      dll<T> adjList;   //adjacency list
      bool visited = false;
      int parent;       //to store parent
      int dist_from_source;   //to store shortest distance from source vertex
      int explored  = false;  //to check if shortes path to the current vertex is calculated
};

template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
class Graph{
      public:
            int V;
            T1 *vertex;
            Graph(){
                  //Storing Graph Information
                  cin>>V;
                  vertex = new T1[V];     //T1 = graphNode<edge>
                  int E, a, b, wt;
                  cin>>E;
                  cout<<"Print: "<<V<<' '<<E<<endl;
                  for(int i =0; i<E; i++){
                        cin>>a>>b>>wt;
                        vertex[a].adjList.push_back({b, wt});
                        vertex[b].adjList.push_back({a, wt});
                  }

            }
            void print();
            void dijkstra(int source);
};

template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::print(){
      cout<<"---------------Graph-------------\n";
      for(int i =0; i<V; i++){
            cout<<i<<": ";
            for(class dll<T2>::iterator itr= vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  cout<<(*itr).ind<<','<<(*itr).wt<<"  ";
            }
            cout<<endl;
      }
      cout<<"-----------------------------------\n";
}

//item in priority_queue
class item{
public:
      int key = INT_MAX;           //distance from source vertex
      int index;                    //index of vertex
      friend edge;
      friend graphNode<edge>;
      friend Graph<graphNode<edge>, edge>;
};

template<class T1, class T2>  //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::dijkstra(int source){
      //Making priority_queue
      cout<<"Dijkstra Started\n";
      item *arr = new item[V];
      for(int i =0; i<V; i++){
            arr[i].index = i;
      }
      queue_priority<item> heap = build_heap(arr, V, 100);
      heap.decrease_key(source, 0);
      heap.print_heap();
      while(heap.size()!=0){
            item temp = heap.delete_min();
            cout<<"deleted: "<<temp.index<<' '<<temp.key<<endl;
            vertex[temp.index].dist_from_source = temp.key;
            vertex[temp.index].explored = true;
            int i = temp.index;
            for(class dll<T2>::iterator itr = vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  cout<<"Searching: "<<(*itr).ind<<' '<<(*itr).wt<<' '<<heap.arr[heap.pos[(*itr).ind]].index<<' '<<heap.arr[heap.pos[(*itr).ind]].key<<endl;
                  if(vertex[(*itr).ind].explored == false && temp.key + (*itr).wt < heap.arr[heap.pos[(*itr).ind]].key){
                        heap.decrease_key(heap.pos[(*itr).ind], temp.key + (*itr).wt);
                        vertex[(*itr).ind].explored = true;
                  }
            }
      }

      cout<<"SOURCE: "<<source<<endl;
      for(int i =0; i<V; i++){
            cout<<"Index: "<<i<<" distance: "<<vertex[i].dist_from_source<<endl;
      }
}

int main(int argc, char const *argv[]) {
      Graph<graphNode<edge>, edge> G;
      G.print();

      int source; //index of source vertex
      cin>>source;
      G.dijkstra(source);
      return 0;
}
