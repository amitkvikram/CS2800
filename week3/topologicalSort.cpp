/*
 Name: Amit Vikram Singh
 Roll No.: 111601001
 Problem: topologicalSort
 Date: 23Jan, 2018
*/

#include<bits/stdc++.h>
#include "dll.h"
#include "stack.h"
using namespace std;

/*********************Back edge Information***************************************/
class backEdge{
public:
  int i;
  int j;
};

/*********************class structured for information about each node***********/
class node{
public:
  int parent;
  int previsit = 0;
  int postvisit = 0;
  List *adjList;  ///Adjacent list to store the adjacent Vertices
  bool visited = false;
  node();
};

/*********************class structured for information about graph************/
class graph{
public:
  int v;    //no of vertices
  node *vertex;
  graph(int V);
  void print_graph();
  void dfs(stack1 **Top, int v_i, int *clock);
  backEdge checkBackEdge();
};

/*****************Constructor for object of class graph************/
graph::graph(int V){
  v = V;
  vertex = new node[v];
}

/*****************Constructor for object of class node*************/
node::node(){
 this->adjList = dll_list();
 parent = 1;
}

//Member function of class graph to print graph(each vertex adjacency list)
void graph::print_graph(){
  for(int i =0; i<v; i++){
    dll_print(&(vertex[i].adjList));
  }
}

/************ Reading Input File *****************/
graph* read_input(){
  printf("reading input\n");
    int v;   //number of vertices in graph
    scanf("%d", &v); //scanning number of vertices in the graph
    graph* G = new graph(v); //initialize graph

    int temp;

    for(int i =0; i<G->v; i++){
      scanf("%d", &temp);
      while(temp != -1){
          dll_push_back(&(G->vertex[i].adjList), temp);
          scanf("%d", &temp);
      }
    }
    return G;
}

/********************Checking for back edge******************/
backEdge graph::checkBackEdge(){
  backEdge index;
  index.i = -1;
  index.i = -1;
  for(int i =0; i<v; i++){
    DLL_NODE *temp = vertex[i].adjList->front;
    for(int j =0; j<dll_size(&(vertex[i].adjList)); j++){
      int adj_i = temp->data;
      if(vertex[adj_i].previsit<vertex[i].previsit && vertex[adj_i].postvisit>vertex[i].postvisit){//backedge found
        index.i = i;
        index.j = adj_i;
        return index;
      }
      temp = temp->next;
    }
  }
  return index;    //backedge not found
}

/**************DFS(finding edge type)**************************/
void graph::dfs(stack1 **Top, int v_i, int *clock){
  vertex[v_i].visited = true;
  vertex[v_i].previsit = *clock;
  *clock = *clock+1;
  DLL_NODE *temp = vertex[v_i].adjList->front;

  for(int i = 0; i<dll_size(&(vertex[v_i].adjList)); i++){
    int data = temp->data;
    if(vertex[data].visited == false) {
      vertex[data].parent = v_i;
      dfs(Top, data, clock);
    }
    temp = temp->next;
  }

  vertex[v_i].postvisit = *clock;
  *clock = *clock + 1;
  stackPush(Top, v_i);    //pushing current element in stack;
}

/**************Main Begins Here********************************/
int main(int argc, char const *argv[]){
  graph* G = read_input();
  printf("------Adjacency List------\n");
  G->print_graph();
  printf("----------------------------\n");
  stack1 *Top = NULL;
  int clock= 1;
  for(int i =0; i<G->v; i++){
    if(G->vertex[i].visited == false) G->dfs(&Top, i, &clock);
  }
  backEdge tmp = G->checkBackEdge();     //Calling function to check for backedge;
  if(tmp.i!=-1){    //A directed cycle is detected
    cout<<"A directed cycle is detected\n";
    while(!isEmpty(&Top)){
      stackPop(&Top);
    }
    // cout<<tmp.i<<' ' <<tmp.j<<endl;
    int i = tmp.i;
    stackPush(&Top, tmp.i);
    while(i!=tmp.j){
      stackPush(&Top, G->vertex[i].parent);
      i = G->vertex[i].parent;
    }
    while(!isEmpty(&Top)){
      int tmp = stackPop(&Top);
      cout<<tmp<<"-->";
    }
    cout<<tmp.j;
    cout<<endl;
    return 0;
  }

  printf("---------Topological Order-----------\n");
  cout<<"Start-->";
  while(!isEmpty(&Top)){
    int tmp = stackPop(&Top);
    cout<<tmp<<"-->";
  }
  cout<<"End"<< endl;
  return 0;
}
