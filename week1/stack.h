#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
	int data; //movieName stores the name of movie
	struct stack *next; //ponter to next node in stack
};


typedef struct stack stack;  // setting alias "stack" for "struct stack"

//stackTop prints the top of Stack
void stackTop(stack **Topptr);

void stackPush(stack **Topptr ,int data);

int stackPop(stack **Topptr);

int isEmpty(stack **Topptr);
