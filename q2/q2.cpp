/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 27Feb, 2018
  Problem: Mid Sem LabQuiz1_Q2
  Use flag -std=c++11 while compiling[g++ -std=c++11 q2.cpp]
*/

#include <iostream>
#include "linked_list.h"
#include "priority_queue.h"
using namespace std;
int inf = 1000000;

//edge information
class edge{
public:
      int ind;    //destination vertex
      int wt;     //edge weight
      int flag;	// flag = 1 if road is under repair
};

//Each Vertex and its adjacent list information
template<class T>   //T = edge
class graphNode{
public:
      dll<T> adjList;   //adjacency list
      int parent = -1;       //to store parent
      int dist_from_source;   //to store shortest distance from source vertex
      int explored  = false;  //to check if shortest path to the current vertex is calculated
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
                        vertex[a].adjList.push_back({b, wt, 0});	
                  }

            }
            void reset();
            void print();                       //function to print graph infomrmation
            void dijkstra(int source, int dest);
};

//Reset for parent and explored information for each round
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::reset(){
	for(int i =0; i<V; i++){
		vertex[i].explored = false;
		vertex[i].parent = -1;
	}
}

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
      int key = inf;           //distance from source vertex
      int index;                    //index of vertex
};

template<class T1, class T2>  //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::dijkstra(int source, int dest){
	   int found = 0;		//flag to check if root is found or not
      //Making priority_queue
      item *arr = new item[V];
      for(int i =0; i<V; i++){
            arr[i].index = i;
      }
      queue_priority<item> heap = build_heap(arr, V, 100);
      heap.decrease_key(source, 0);
      vertex[source].parent = 0;
      while(heap.size()!=0){
            item temp = heap.pop();
            vertex[temp.index].dist_from_source = temp.key;
            vertex[temp.index].explored = true;		//Shortest distance for temp.index is found
            int i = temp.index;
            if(i== dest){
            	if(temp.key!=inf){
            		found = 1;						//Shortes route between source and destination is found
            	}
            } 
            
            //Traversing through adjacency list of i
            for(class dll<T2>::iterator itr = vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  int heap_pos = heap.pos[(*itr).ind];          //position of vertex in priority_queue
                  int ind = (*itr).ind;                     //index of vertex
                  if((*itr).flag == 0){
                     //Road is not under repair
		               if(vertex[ind].explored == false && temp.key + (*itr).wt < heap.arr[heap_pos].key ){  //If true relax
		                     heap.decrease_key(heap_pos, temp.key + (*itr).wt); 	               //decreasing key
		                     vertex[ind].parent = temp.index;                                  //storing parent
		               }
		           }	
		           else{
		            (*itr).flag = 0;	//Set flag = 0 for next round(no more needed flag information for this edge in this round)
		           }
            } 	
      }

 		cout<<"\n----------SHORTEST PATH-----------\n"<<"SOURCE: "<<source<<endl;
      cout<<"Destination:"<<dest;
      if(found == 0){
      	cout<<"\nno route found\n";
      	return;
      }
		cout<<"  Distance:"<<vertex[dest].dist_from_source<<" Path: ";
      int ind = dest;
      while(ind!=source && vertex[ind].parent!=-1){
            cout<<ind<<"<---";
            ind = vertex[ind].parent;
      }
      cout<<ind<<endl;
}

int main(int argc, char const *argv[]) {
      Graph<graphNode<edge>, edge> G;     //initializing graph object
      G.print();                          //printing graph information

      int k;				//No of rounds
      cin>>k;
      for(int i =0; i<k; i++){
         G.reset();		//Reset explored and parent information 
      	int l;			//No of roads under repair
      	cin>>l;
      	int a,b;
      	for(int i =0; i<l; i++){
      		cin>>a>>b;
      		for(dll<edge>::iterator itr= G.vertex[a].adjList.begin(); itr!= G.vertex[a].adjList.end(); itr++){
                  if((*itr).ind == b) (*itr).flag = 1;
            }
      		
      	}
      	   int source, dest;
      	   cin>>source>>dest;
		      G.dijkstra(source, dest);     //calling dijkstra function to find and print the shortest distance of all vertices from source vertex
      }
      
      return 0;
}
