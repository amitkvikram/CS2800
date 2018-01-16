/*
  Problem Name:Ex5
  Programmers'Name: Amit Vikram Singh
  Roll No.:111601001
  Data:15/08/2017
*/

#include<stdio.h>
#include<stdlib.h>

struct DLLNode{
	int data;
	struct DLLNode *next; //ponter to next node in linked list
      	struct DLLNode *prev; //ponter to previous node in linked list
};

typedef struct DLLNode Node; // setting alias "Node" for "struct Node"

int dllEmpty(Node **Headptr){
	Node *tempptr = *Headptr;
	if(tempptr == NULL){
		return 1;
	}
	return 0;
}

void dllFrontPush(Node **Headptr, int data){                                  
       Node *tempptr=*Headptr;
             Node *temp= (Node*)malloc(sizeof(Node));  //Dynamically allocating memory.
             temp->data=data;
             temp->next=NULL;
             if(*Headptr==NULL){       //Checking if list is empty
                  *Headptr=temp;
                  tempptr=*Headptr;
                  temp->prev=NULL;
             }
             else{
                   temp->prev=tempptr;
                   tempptr->next=temp;
                   tempptr=tempptr->next;
             }
}

void dllEndPush(Node **Headptr, int data){
	Node *tempptr = *Headptr;
	Node *temp= (Node*)malloc(sizeof(Node));  //Dynamically allocating memory.
	     temp->data=data;
	     temp->next=NULL;
	     temp->prev = NULL;
	if(*Headptr==NULL){       //Checking if list is empty
                  *Headptr=temp;
                  tempptr=*Headptr;
                  temp->prev=NULL;
        }
       
        while(tempptr->next!=NULL){
        	tempptr = tempptr->next;
        }
        
        temp->prev = tempptr;
        tempptr->next = temp;
} 
       		
int dllPopLast(Node **Headptr){
	if(dllEmpty(Headptr)){
		return -1;
	}
	
	Node *tempptr = *Headptr;
	while(tempptr->next!=NULL){
		tempptr = tempptr->next;
	}
	
	int tempData = tempptr->data;

	Node *tempPrev = tempptr->prev;
	free(tempptr);
	if(tempPrev) tempPrev->next = NULL;
	
	return tempData;
}	
	
int dllPopFirst(Node **Headptr){
	if(dllEmpty(Headptr)){
		return -1;
	}
	
	int tempData = (*Headptr)->data;
	Node *tempptr = *Headptr;
	*Headptr = (*Headptr)->next;
	free(tempptr);
	
	return tempData;
}
	
void dllFree(Node **Headptr){    //deallocate the dynamic memory allocated for list
      Node *tempptr= *Headptr;
      while(tempptr!=NULL){
            Node *temp=tempptr;
            tempptr= tempptr->next;
            free(temp);
      }
}

int main(){
	int temp;
	Node *Head = NULL;
	scanf("%d", &temp);
	dllFrontPush(&Head, temp);
	temp = dllPopFirst(&Head);
	printf("\n%d\n", temp);
	scanf("%d", &temp);
	dllFrontPush(&Head, temp);
	temp = dllPopFirst(&Head);
	printf("\n%d\n", temp);
	temp = dllPopFirst(&Head);
	printf("\n%d\n", temp);

	return 0;
}
