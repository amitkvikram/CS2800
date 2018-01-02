#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct DLL_NODE{
	void *data;
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
bool dll_empty(List **my_list);

List* list(){
printf("Here");	
	List *Temp = (List*)malloc(sizeof(List));
	Temp->front = Temp->end = NULL;
	Temp->dllSize = 0;
	return Temp;
}

void dll_push_front(List **my_list, void *data){	//Push one element at front of the double linked list
printf("Here");	
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
	
	printf("%d\n", *((int*)((*my_list)->front->data)));
}

void dll_push_back(List **my_list, void *data){		//Push one element at end of the double linked list
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

void* dll_back(List **my_list){				//Return last element of double linked list
	if(dll_empty(my_list)){
		return NULL;
	}
	return (*my_list)->end->data;
}

void* dll_front(List **my_list){			        //Return first element of double linked list
	if(dll_empty(my_list)){
		return NULL;
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

//void free_memory(){}

int main(){
	List *my_list = list();
	int temp1 = 10;
	int temp2 = 20;
	dll_push_front(&my_list, &temp1);
	dll_push_front(&my_list, &temp2);
	//printf("%i\n",((int*)dll_front(&my_list)));
	//printf("%d\n",(int*)dll_front(&my_list));
	//printf("%d\n",(int*)dll_front(&my_list));
	return 0;
}



