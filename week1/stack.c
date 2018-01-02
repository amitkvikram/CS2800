/*
  Problem Name:Ex1
  Programmers'Name: Amit Vikram Singh
  Roll No.:111601001
  Data:29/08/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
	int data; //movieName stores the name of movie
	struct stack *next; //ponter to next node in stack
};

int stackSize=0;    //stackSize stores size of Stack

typedef struct stack stack;  // setting alias "stack" for "struct stack"

//stackTop prints the top of Stack
void stackTop(stack **Topptr){   
        if(!(*Topptr)){                               //Checks if stack is empty
		printf("4.stackTop: Stack is empty\n");
		return;
	}
	printf("4.stackTop: %d\n", (*Topptr)->data);
	return;
}

//stackPush pushes new element at the top of Stack
void stackPush(stack **Topptr ,int data){
		stackSize++;
		stack *temp= (stack*)(malloc(sizeof(stack)));
		temp->data = data;
		temp->next= *Topptr;
		*Topptr= temp;
}

//stackPop deletes and returns top of stack
int stackPop(stack **Topptr){
	if(!(*Topptr)){                    //Checks if stack is empty
		printf("Stack is empty\n");
		return -1;               //returns NULL if string is empty
	}
	stackSize--;
	stack *temp= *Topptr;
	int tempData = temp->data;
	*Topptr=(*Topptr)->next;
	free(temp);
	return tempData;
}	

//isempty returns 1 if list is empty else returns 0
int isEmpty(stack **Topptr){
	if(!(*Topptr)){     //Checks if stack is empty
		return 1;
	}
	return 0;
}

	
	 
	

