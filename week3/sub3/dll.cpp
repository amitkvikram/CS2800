#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct DLL_NODE{
	int data;
	struct DLL_NODE *next;
	struct DLL_NODE *prev;
};

typedef struct DLL_NODE DLL_NODE;

struct List{
	DLL_NODE *front;
	DLL_NODE *end;
	int dllSize;
};

typedef struct List List;

List* dll_list(){
	List *Temp = (List*)malloc(sizeof(List));
	Temp->front = Temp->end = NULL;
	Temp->dllSize = 0;
	return Temp;
}

bool dll_empty(List **my_list);

void dll_push_front(List **my_list, int data){	//Push one element at front of the double linked list
	DLL_NODE *Temp = (DLL_NODE*)malloc(sizeof(DLL_NODE));	//Dynamically Allocating Memory
	Temp->data = data;
	Temp->next = NULL;
	Temp->prev = NULL;
	(*my_list)->dllSize++;
	if((*my_list)->front == NULL){	//If list is Empty
		(*my_list)->front = Temp;
		(*my_list)->end = Temp;
	}
	else{
		Temp->next = (*my_list)->front;
		(*my_list)->front->prev = Temp;
		(*my_list)->front = Temp;
	}
}

void dll_push_back(List **my_list, int data){		//Push one element at end of the double linked list
	DLL_NODE *Temp = (DLL_NODE*)malloc(sizeof(DLL_NODE));	//Dynamically Allocating Memory
	Temp->data = data;
	Temp->next = NULL;
	Temp->prev = NULL;
	(*my_list)->dllSize++;
	if((*my_list)->front == NULL){	//If list is Empty
		(*my_list)->front = Temp;
		(*my_list)->end = Temp;
	}

	else{
		(*my_list)->end->next = Temp;
		Temp->prev = (*my_list)->end;
		(*my_list)->end = Temp;
	}
}

void dll_pop_back(List **my_list){				//Delete last element of double linked list
	if(dll_empty(my_list)){
		return;
	}
	DLL_NODE *Temp = (*my_list)->end;
	(*my_list)->dllSize--;
	if(Temp->prev){
		Temp->prev->next = NULL;
	}
	else{
		(*my_list)->front = NULL;
	}

	(*my_list)->end = Temp->prev;
	free(Temp);					//Free the allocated memory for deleted node
}

void dll_pop_front(List **my_list){				//Delete first element of double linked list
	if(dll_empty(my_list)){
		return;
	}
	DLL_NODE *Temp = (*my_list)->front;
	(*my_list)->dllSize --;
	if(Temp->next){
		Temp->next->prev = NULL;
	}
	else{
		(*my_list)->end = NULL;
	}

	(*my_list)->front = Temp->next;
	free(Temp);					//Free the allocated memory for deleted node
}

int dll_back(List **my_list){				//Return last element of double linked list
	if(dll_empty(my_list)){
		return INT_MAX;
	}
	return (*my_list)->end->data;
}

int dll_front(List **my_list){			        //Return first element of double linked list
	if(dll_empty(my_list)){
		return INT_MAX;
	}
	return (*my_list)->front->data;
}

int dll_size(List **my_list){				//Returns size of double linked list
	return (*my_list)->dllSize;
}

bool dll_empty(List **my_list){				//Returns true if list is empty
	if((*my_list)->front == NULL) return true;
	else return false;
}

DLL_NODE* dll_search(List **my_list, int data){	//Searching for data in double linked list
	DLL_NODE *Temp = (*my_list)->front;
	for(int i =0; i<(*my_list)->dllSize; i++){
		if(data == Temp->data){
			return Temp;																//If found return pointer to particular node
		}
		Temp=Temp->next;
	}

	return NULL;																	//If not found return NULL
}

void dll_print(List **my_list){
	DLL_NODE* Temp = (*my_list)->front;
	for(int j = 0; j<dll_size(my_list); j++){
		printf("%d ",Temp->data);
		Temp = Temp->next;
	}
	printf("\n");
}

void free_memory(List **my_list){
	while(!dll_empty(my_list)){
		dll_pop_front(my_list);
	}
	free(*my_list);
}
