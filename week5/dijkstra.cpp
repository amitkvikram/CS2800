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

//Each Vertex and its adjacent list information
template<class T>   //T = edge
class graphNode{
public:
      dll<T> adjList;   //adjacency list
      bool visited = false;
      int parent = -1;       //to store parent
      int dist_from_source;   //to store shortest distance from source vertex
      int explored  = false;  //to check if shortes path to the current vertex is calculated
};

//Garaph API
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
                  cout<<"#Vertex:"<<V<<" #Edge:"<<E<<endl;
                  //Creating Adjacent list
                  for(int i =0; i<E; i++){
                        cin>>a>>b>>wt;                    //and edge of weight=wt between vertex a and b;
                        vertex[a].adjList.push_back({b, wt});
                        vertex[b].adjList.push_back({a, wt});
                  }

            }
            void print();                       //function to print graph infomrmation
            void dijkstra(int source);
};

//Print vertex and its adjacent list
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
}

//item in priority_queue
class item{
public:
      int key = INT_MAX;           //distance from source vertex
      int index;                    //index of vertex
};

template<class T1, class T2>  //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::dijkstra(int source){
      //Making priority_queue
      item *arr = new item[V];
      for(int i =0; i<V; i++){
            arr[i].index = i;
      }
      queue_priority<item> heap = build_heap(arr, V, 100);
      heap.decrease_key(source, 0);
      vertex[source].parent = 0;
      while(heap.size()!=0){
            item temp = heap.delete_min();
            vertex[temp.index].dist_from_source = temp.key;
            vertex[temp.index].explored = true;
            int i = temp.index;
            for(class dll<T2>::iterator itr = vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  int heap_pos = heap.pos[(*itr).ind];          //position of vertex in priority_queue
                  int ind = (*itr).ind;                     //index of vertex
                  if(vertex[ind].explored == false && temp.key + (*itr).wt < heap.arr[heap_pos].key){
                        heap.decrease_key(heap_pos, temp.key + (*itr).wt);                //decreasing key
                        vertex[ind].parent = temp.index;                                  //storing parent
                  }
            }
      }

      //Printing shortest distance
      cout<<"\n----------SHORTEST PATH-----------\n"<<"SOURCE: "<<source<<endl;
      for(int i =0; i<V; i++){
            if(vertex[i].explored == true) cout<<"Destination:"<<i<<"  Distance:"<<vertex[i].dist_from_source<<" Path: ";
            int ind = i;
            while(ind!=source && vertex[ind].parent!=-1){
                  cout<<ind<<"<---";
                  ind = vertex[ind].parent;
            }
            cout<<ind<<endl;
      }
}

int main(int argc, char const *argv[]) {
      Graph<graphNode<edge>, edge> G;     //initializing graph object
      G.print();                          //printing graph information

      int source; //index of source vertex
      cin>>source;
      G.dijkstra(source);     //callign dijkstra function to find and print the shortest distance of all vertices from source vertex
      return 0;
}
