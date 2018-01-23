#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack1{
	int data; //movieName stores the name of movie
	struct stack1 *next; //ponter to next node in stack1
};


typedef struct stack1 stack1;  // setting alias "stack1" for "struct stack1"

//stack1Top prints the top of stack1
void stackTop(stack1 **Topptr);

void stackPush(stack1 **Topptr ,int data);

int stackPop(stack1 **Topptr);

int isEmpty(stack1 **Topptr);
