/*
 Name: Amit Vikram Singh
 Roll No.: 111601001
 Problem: topologicalSort
 Date: 23Jan, 2018
*/

#define rep(i, a, b) for(int i =a; i<b; i++)
#include<bits/stdc++.h>
#include "linked_list.h"
#include "stack.h"

/*********************Back edge Information***************************************/
class backEdge{
public:
  int i;
  int j;
};

//edge information
class edge{
public:
      int dest;    //destination vertex
      int wt;     //edge weight
};

/*********************class structured for information about each node***********/
template<class T>       //T = edge
class graphNode{
public:
  int parent = -1;
  dll<T> adjList;  ///Adjacent list to store the adjacent Vertices
  bool visited = false;
  node();
};

/*********************class structured for information about graph************/
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
class graph{
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
      void dfs(my_stack<int> &st, int v_i, int *clock);
      void reset();
      backEdge detect_cycle();
};

template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::reset(){
      rep(i, 0, V){
            vertex[i].visited = false;
            vertex[i].parent = -1;
      }
}

//ADD EDGE
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

//DFS for detecting Cycle
backEdge dfs_cycle(int s){
      vertex[s].visited = true;
      in_stack[s] =true;
      for(class dll<T2>::iterator itr= vertex[s].adjList.begin(); itr!= vertex[s].adjList.end(); itr++){
            if(in_stack[*itr] == true) return {s, *itr};
            if(visited[*itr] == false){
                  backEdge tmp = dfs(*itr);
                  if(tmp.i!=-1) return  tmp;
            }
      }
      in_stack[s] = false;
      return {-1, -1};
}

//Detecting Cycle in graph
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
backEdge Graph<T1, T2>::detect_cycle(){
      reset();
      bool in_stack[V] = {false};
      rep(i, 0, V){
            if(vertex[i].visited == false){
                  backEdge tmp = dfs_cycle(i, in_stack);
                  if(tmp.i!=-1) return tmp;
            }
      }
      return {-1, -1};
}
