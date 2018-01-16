#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

struct Node{
      int data;
      struct Node *next;
};

typedef struct Node node;

struct Queue{
      node *front;
      node *end;
};

typedef struct Queue queue;

queue *createQueue();

//checks if Queue is empty or not
int isEmptyQueue(queue **Q);

//Inserts an element at	the end of the queue
void enQueue (queue **Q, int x);

//deletes and returns element at the front of queue
int dequeue(queue **Q);
