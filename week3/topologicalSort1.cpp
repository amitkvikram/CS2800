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
};

/*********************class structured for information about each node***********/
template<class T>       //T = edge
class graphNode{
public:
  int parent = -1;
  dll<T> adjList;  ///Adjacent list to store the adjacent Vertices
  bool visited = false;
};

/*********************class structured for information about graph************/
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

      void add_edge(int a, int b);
      void print();
      void dfs(my_stack<int> &st, int v_i, int *clock);
      void reset();
      backEdge detect_cycle();
      backEdge dfs_cycle(int s, bool *in_stack);
      void dfs_topological(int s, my_stack<int> &st);
      void topologicalSort();
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
void Graph<T1, T2>::add_edge(int a, int b){
      vertex[a].adjList.push_back({b});
}

//Print vertex and its adjacent list
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::print(){
      cout<<"-----Graph---------\n";
      for(int i =0; i<V; i++){
            cout<<i<<": ";
            for(class dll<T2>::iterator itr= vertex[i].adjList.begin(); itr!= vertex[i].adjList.end(); itr++){
                  cout<<(*itr).dest<<"  ";
            }
            cout<<endl;
      }
      cout<<"---------------------\n";
}

//DFS for detecting Cycle
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
backEdge Graph<T1, T2>::dfs_cycle(int s, bool *in_stack){
      vertex[s].visited = true;
      in_stack[s] =true;
      for(class dll<T2>::iterator itr= vertex[s].adjList.begin(); itr!= vertex[s].adjList.end(); itr++){
            if(in_stack[(*itr).dest] == true) return {s, (*itr).dest};
            if(vertex[(*itr).dest].visited == false){
                  vertex[(*itr).dest].parent = s;
                  backEdge tmp = dfs_cycle((*itr).dest, in_stack);
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

//DFS for storing topological Order
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::dfs_topological(int s, my_stack<int> &st){
      vertex[s].visited = true;
      for(class dll<T2>::iterator itr= vertex[s].adjList.begin(); itr!= vertex[s].adjList.end(); itr++){
            if(vertex[(*itr).dest].visited == false){
                  dfs_topological((*itr).dest, st);
            }
      }
      st.push(s);
}

//Print Topological Order
template<class T1, class T2>   //T1 = <graphNode<edge> T2 = edge
void Graph<T1, T2>::topologicalSort(){
      backEdge tmp = detect_cycle();
      if(tmp.i!=-1){
            cout<<"CYCLE FOUND\n";
            int x = tmp.i;
            int y = tmp.j;
            //return;
            while(x!=y){
                  cout<<x<<"<--";
                  x = vertex[x].parent;
            }
            cout<<x<<endl;
            return;
      }

      my_stack<int> st;
      reset();
      rep(i, 0, V){
            if(vertex[i].visited == false){
                  dfs_topological(i, st);
            }
      }
      while(!st.is_empty()){
            cout<<st.top()<<' ';
            st.pop();
      }
      cout<<endl;
}

int main(){
      int n, m;
      cin>>n>>m;
      Graph<graphNode<edge>, edge> G(n, m);
      int a, b;
      rep(i, 0, m){
            cin>>a>>b;
            G.add_edge(a, b);
      }
      G.print();
      G.topologicalSort();
}
