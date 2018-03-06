/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 5 March, 2018
  Problem: Bellman Ford Algorithm Implementation
*/

#include<iostream>
#include "linked_list.h"
using namespace std;
#define rep(i, a, b) for(int i =a; i<b; i++)
#define inf 10000000

//edge information
class edge{
public:
      int dest;     //destination vertex
      int wt;       //edge weight
};

//Each Vertex and its adjacent list information
class graphNode{
public:
      dll<edge> adjList;      //adjacency list
      int dist;
      int parent = -1;        //to store parent
      void reset(){
            dist = inf;
      }
};

int main(){
      int n, m;
      cin>>n>>m;
      graphNode *G = new graphNode[n];    //Initializing Graph
      int a, b, wt;

      rep(i, 0, m){
            cin>>a>>b>>wt;
            G[a].adjList.push_back({b, wt});
      }

      rep(i, 0, n){
            G[i].reset();      //setting distance infinity
      }

      int s;      //Source Vertex
      cin>>s;
      G[s].dist = 0;    //Set distance of source vertex 0
      int flag ;

      //Bellman Ford
      rep(i, 1, n){
            flag = 0;
            rep(j, 0, n){
                  for(dll<edge>::iterator it = G[j].adjList.begin(); it!=G[j].adjList.end(); it++){
                        if(G[j].dist!=inf && G[j].dist + (*it).wt < G[(*it).dest].dist){
                              flag = 1;
                              G[(*it).dest].dist = G[j].dist + (*it).wt;      //relaxation
                              G[(*it).dest].parent = j;
                        }
                  }
            }
            if(flag == 0)  break;   //None of the edge is relaxed
      }

      bool neg_cycle = false;

      //Detecting Negative Cycle
      if(flag == 1){
                  rep(j, 0, n){
                  for(dll<edge>::iterator it = G[j].adjList.begin(); it!=G[j].adjList.end(); it++){
                        if(G[j].dist + (*it).wt < G[(*it).dest].dist && G[j].dist!=inf){
                              neg_cycle = true;             //Negative Cycle Found
                              break;
                        }
                  }
                  if(neg_cycle == true) break;
            }
      }

      if(neg_cycle == true){
            cout<<"Negative weight cycle found\n";
      }
      else{
            rep(i, 0, n){
                  cout<<i<<": ";
                  if(G[i].dist == inf){
                        cout<<"Unreachable\n";
                  }
                  else{
                        cout<<"Dist = "<<G[i].dist<<"   Path: ";
                        int curr = i;
                        while(curr!=s){
                              cout<<curr<<"<--";
                              curr = G[curr].parent;
                        }
                        cout<<curr<<endl;
                  }

            }
      }
      return 0;
}
