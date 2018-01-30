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

List* dll_list();
bool dll_empty(List **my_list);
void dll_push_front(List **my_list, int data);
void dll_push_back(List **my_list, int data);
void dll_pop_back(List **my_list);
void dll_pop_front(List **my_list);
int dll_back(List **my_list);
int dll_front(List **my_list);
int dll_size(List **my_list);
DLL_NODE* dll_search(List **my_list, int data);
void dll_print(List **my_list);
void dll_free_memory(List **my_list);
