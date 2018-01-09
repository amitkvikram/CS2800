/*
 Name: Amit Vikram Singh
 Roll No.: 111601001
 Problem: Depth First Search using adjacency lists
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "dll.h"

struct graphNode{
   List *adjList;   //pointer to adjacency list for a node
   int previsit;    //time of previsit
   int postvisit;   //time of postvisit
   int parent;
   bool visited;
};

typedef struct graphNode graphNode;

struct graph{
  graphNode *vertex;
  int V;            //Number of Vertices in the graph
};

typedef struct graph graph;

/******** Inititalizing Graph**************/
graph* initialize_graph(int v){
  graph *G = (graph*)malloc(sizeof(graph));
  G->V = v;
  G->vertex = (graphNode*)(malloc(G->V*sizeof(graphNode)));
  if(G->vertex == NULL){
    printf("Error in graph Initialization");
    return NULL;
  }

  for(int i =0; i<G->V; i++){
    G->vertex[i].visited = false; //Setting all vertex as not visited initially
    G->vertex[i].previsit = 0;
    G->vertex[i].postvisit = 0;
  }
  return G;
}
/****** Initialized graph ************/

/************ Reading Input File *****************/
graph* read_input(char FileName[]){
    FILE *fp;
    fp = fopen(FileName, "r");
    if(fp == NULL){
      printf("Error in opening input file\n");
      return NULL;
    }
    int v;   //number of vertices in graph
    fscanf(fp, "%d", &v); //scanning number of vertices in the graph
    graph* G = initialize_graph(v); //calling function to initialize graph

    int temp;

    for(int i =0; i<G->V; i++){
      fscanf(fp, "%d", &temp);
      G->vertex[i].adjList = list();
      while(temp != -1){
          dll_push_back(&(G->vertex[i].adjList), temp);
          fscanf(fp, "%d", &temp);
      }
    }
    fclose(fp);
    return G;
}

//Graph Exploration
void dfs(graph *G, int v, int *clock){
    G->vertex[v].visited = true;

    /*********Previsit Begin**************/
    G->vertex[v].previsit = *clock;
    (*clock)+=1;
    /********Previsit End***************/

    /********exploring adjacent vertices of current node begin********/
    DLL_NODE* Temp = G->vertex[v].adjList->front;
    for(int i =0; i<dll_size(&(G->vertex[v].adjList)); i++){
        int tmp = Temp->data;

        if(G->vertex[tmp].visited == false){
          G->vertex[tmp].parent = v;
          dfs(G, tmp, clock);
        }

        Temp = Temp->next;
    }
    /*******exploring adjacent vertices of current node end**********/

    /********postvisit begin*************/
    G->vertex[v].postvisit = *clock;
    (*clock)+=1;
    /********postvisit end***************/
}

//Printing Edge type
void print_edge_type(graph *G, int root){
  printf("----Printing Edge Type----\n");
  printf("Vertex | Edge Type\n-------|----------\n");
  for(int i =0; i<G->V; i++){
    DLL_NODE *Temp = G->vertex[i].adjList->front;
    for(int j= 0; j<dll_size(&(G->vertex[i].adjList)); j++){
        int tmp = Temp->data;

        if(G->vertex[i].previsit < G->vertex[tmp].previsit){
          if(G->vertex[tmp].parent == i)  printf("%d-%d   : %s\n", i, tmp, "Tree Edge");
          else printf("%d-%d   : %s\n", i, tmp, "Forward Edge");
        }
        else {
          if(G->vertex[tmp].previsit > G->vertex[i].postvisit) printf("%d-%d   : %s\n", i, tmp, "Cross Edge");
          else printf("%d-%d   : %s\n", i, tmp, "Back Edge");
        }
        Temp = Temp->next;
    }
  }
  printf("\n");
}

/*********** Free Memory************/
void free_memory(graph* G){
  for(int i =0; i<G->V; i++){
    dll_free_memory((&G->vertex[i].adjList));
  }
  free(G->vertex);
  free(G);
}

/********Main Begins*********************/
int main(int argc, char const *argv[]) {
  char FileName[50];
  printf("Please Enter File Name: ");
  scanf("%s",FileName);
  int root;
  printf("Please Enter root vertex: ");
  scanf("%d", &root);
  graph* G = read_input(FileName);
  if(G==NULL){
   return 0;
  }
  printf("------Adjacency List------\n");
  for(int i = 0; i<G->V; i++){
    dll_print(&(G->vertex[i].adjList));
  }

  int clock = 1;
  G->vertex[root].parent = -1;
  dfs(G, root, &clock);       //calling function for graph exploration
  for(int i =0; i<G->V; i++){
    if(G->vertex[i].visited == false) dfs(G, i, &clock);
  }
  printf("-----Exploration time-----\n");
  printf("vertex| Previsit| Postvisit\n");
  for(int i =0; i<G->V; i++){
    printf("  %-4d|   %4d  | %7d\n",i, G->vertex[i].previsit, G->vertex[i].postvisit);
  }

  print_edge_type(G, root);
  free_memory(G);
  return 0;
}
/******Main ends***********************/
