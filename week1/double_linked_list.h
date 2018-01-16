#include<stdio.h>
#include<stdlib.h>

struct DLLNode{
	int data;
	struct DLLNode *next; //ponter to next node in linked list
      struct DLLNode *prev; //ponter to previous node in linked list
};

typedef struct DLLNode Node; // setting alias "Node" for "struct Node"

int dllEmpty(Node **Headptr)
void dllFree(Node **Headptr);
void dllFrontPush(Node **Headptr, int data);
void dllEndPush(Node **Headptr, int data);
int dllPopFirst(Node **Headptr);
int dllPopLast(Node **Headptr);
