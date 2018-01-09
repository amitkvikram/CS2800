/*
   Name: Amit Vikram Singh
   Roll No: 111601001
   Date: 10/10/2017
   Task: 6coloring.c
   Running Programme: enter "make" command in terminal, and output(object) file eulerian.o will be created.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>
#include "queue.h"
#include "CircularLinkedList.h"
#include "stack.h"

struct Graph{		//Structure to store graph information
	int **adjWt;
	int V;    	   //V: no of vertices
	char GraphName[100];
	int isolated;	//No of isolated vertices
	int components;		//No. of Connected Components
};

struct v_Info{			//structure to store information about vertices during BFS
		int dist;	//distance of vertex from root
		bool Checked;	
		int prev;
		int color;
};

typedef struct Graph Graph;
typedef struct v_Info v_Info;

char color[6][20] = {"red","blue","green","brown","gold","yellow"};

Graph *CreateGraph(int V){		//Creating graph data
	Graph *G = (Graph*)malloc(sizeof(Graph));
	G->V = V;
	G->adjWt = (int**)malloc(G->V * sizeof(int*));
	for(int i=0; i<G->V; i++)		//allocating space for adjacency matrix
		G->adjWt[i] = (int*)calloc(G->V, sizeof(int));
	G->components = 0;
	G->isolated = 0;
	
	return G;
}

v_Info* bfsv_Info(Graph *G, int root, int goal){
	v_Info *v_InfoPtr;

	v_InfoPtr = (v_Info*)malloc(G->V * sizeof(v_Info));
	
	v_InfoPtr[root].dist = 0;
	v_InfoPtr[root].Checked = true;
	for(int i=0; i<G->V; i++)		//allocating space for adjacency matrix
		v_InfoPtr[i].color = -1;
	return v_InfoPtr;
}

//Creating dot file
void MakeDot(Graph *G,v_Info *v_I){	
	FILE *fp;
	char GraphName_cp[50];
	strcpy(GraphName_cp,G->GraphName);
	strcat(GraphName_cp,"1.dot");
	printf("%s\n",GraphName_cp);
	fp = fopen(GraphName_cp,"w");
	fprintf(fp, "%s%s%s\n", "graph ",G->GraphName,"{");
	for(int i=0; i<G->V-1; i++){
		int flag =0;
		for(int j=i; j<G->V; j++){
			if(G->adjWt[i][j]>0){
				flag =1;
					fprintf(fp, "%s%d -- %d%s","\t",i,j,";\n");		//coloring path from root to goal
			}
		}
		if(flag == 0) fprintf(fp, "%s%d%s","\t",i,";\n");
	}
	fprintf(fp, "%s%d%s","\t",G->V-1,"\n");
	for(int i=0; i<G->V; i++){
		fprintf(fp, "%s%d%s%s%s%s","\t",i,"[color=",color[v_I[i].color],", style=filled]",";\n");		//coloring path from root to goal
	}
	fprintf(fp, "%s\n", "}");
}



int checkColoring(Graph *G, v_Info *V, int i, int j){
	for(int k = 0; k<G->V ; k++){
		if(G->adjWt[i][k]>0){
			if(V[k].color == j && k!=i) return 0;
		}

	}

	return 1;
}

void Color(Graph *G, v_Info *V){
	for(int i=0; i<G->V; i++){
		for(int j=0; j<6; j++){
			if(checkColoring(G, V, i,j)){
				V[i].color = j;
				break;
			}
		}
	}

	MakeDot(G,V);

}


//Reading Graph file
Graph* Read(FILE **fp){
	char GraphName[50] ;
	fscanf(*fp, " %[^\n]s", GraphName);	//reading graph name
	char GraphType[50];
	fscanf(*fp, " %[^\n]s", GraphType);	//reding graph type
	int num_vertices;
	fscanf(*fp, "%d", &num_vertices);	//scannig number of vertices in the graph
	Graph* G = CreateGraph(num_vertices);
	
	for(int i=0;i<G->V; i++){	//reading adjacecy matrix
		for(int j=0;j<G->V;j++){
			fscanf(*fp, "%1d", &G->adjWt[i][j]);
		}
	}

	strcpy(G->GraphName,GraphName);
	return G;
}

//main begins here
int main(){
	char FileName[50];
	printf("Enter Filename: ");
	scanf("%s", FileName);
	
	FILE *fp;
	fp=fopen(FileName, "r");	//Opening .txt file
	
	 
	 if(fp==0)	//Checking for file error in opening
	 {
	  	printf("Error in opening the file %s.\n", FileName);
	  	return(1);
	 }
	
	Graph *G = Read(&fp);
	fclose(fp);
	v_Info *v_I = bfsv_Info(G, 0, 0);
	Color(G,v_I);
	return 0;

}
//main ends here