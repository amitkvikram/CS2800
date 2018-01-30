/*
  Problem Name:Ex1
  Programmers'Name: Amit Vikram Singh
  Roll No.:111601001
  Data:29/08/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack1{
	int data; //movieName stores the name of movie
	struct stack1 *next; //ponter to next node in stack1
};

int stackSize=0;    //stackSize stores size of stack1

typedef struct stack1 stack1;  // setting alias "stack1" for "struct stack1"

//stackTop prints the top of stack1
void stackTop(stack1 **Topptr){
        if(!(*Topptr)){                               //Checks if stack1 is empty
		printf("--stack1 is empty--\n");
		return;
	}
	printf("stackTop: %d\n", (*Topptr)->data);
	return;
}

//stackPush pushes new element at the top of stack1
void stackPush(stack1 **Topptr ,int data){
		stackSize++;
		stack1 *temp= (stack1*)(malloc(sizeof(stack1)));
		temp->data = data;
		temp->next= *Topptr;
		*Topptr= temp;
}

//stackPop deletes and returns top of stack1
int stackPop(stack1 **Topptr){
	if(!(*Topptr)){                    //Checks if stack1 is empty
		printf("stack1 is empty\n");
		return -1;               //returns NULL if string is empty
	}
	stackSize--;
	stack1 *temp= *Topptr;
	int tempData = temp->data;
	*Topptr=(*Topptr)->next;
	free(temp);
	return tempData;
}

//isempty returns 1 if list is empty else returns 0
int isEmpty(stack1 **Topptr){
	if(!(*Topptr)){     //Checks if stack1 is empty
		return 1;
	}
	return 0;
}
