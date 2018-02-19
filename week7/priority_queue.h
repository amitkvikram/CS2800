/*
 Name: Amit Vikram Singh
 Roll No.: 111601001
 Problem: Priority Queue Implementation
*/
#include<bits/stdc++.h>
using namespace std;

template<class T>
class queue_priority{                         //class for heap
private:
      int heap_capacity;            //variable to store capacity of heap
      int heap_size;                //size of heap
public:
      T *arr;                     //pointer to array in which elemnts of heap are stored
      void min_heapify(int i);      //function to min_heapify at vertex i
      int left_child(int i);        //function to return left child of ith node
      int right_child(int i);       //function to store right child of ith node
      void print_heap();            //function to print heap
      void push(T data);      //function to insert an element in heap
      T pop();             //function to delete minimum element from heap
      T top();
      void heap_sort(bool ascending = false);             //function to sort the heap
      int capacity(){
            return heap_capacity;
      }
      int size(){
            return heap_size;
      }
      void set_heap_size(int n){
            heap_size = n;
      }
      void set_heap_capacity(int n){
            heap_capacity = n;
      }
};

template<class T>
void swap(T *a, T *b){          //function to swap two elements a and b
      T temp = *a;
      *a = *b;
      *b = temp;
}

template<class T>
int queue_priority<T>::left_child(int i){
      return 2*i+1;
}

template<class T>
int queue_priority<T>::right_child(int i){
      return 2*i+2;
}

template<class T>
void queue_priority<T>::min_heapify(int i){
      int smallest_index = i;
      int lchild = left_child(i);
      int rchild = right_child(i);
      if(lchild < heap_size && arr[lchild].key < arr[smallest_index].key){
            smallest_index = lchild;
      }
      if(rchild < heap_size && arr[rchild].key < arr[smallest_index].key){
            smallest_index = rchild;
      }

      if(smallest_index != i){
            swap(arr[smallest_index], arr[i]);
            min_heapify(smallest_index);
      }
}

//Inserting element in heap
template<class T>
void queue_priority<T>::push(T data){
      heap_size++;
      if(heap_size > heap_capacity){
            cout<<"queue_priority exceeding its capacity, returning without inserting"<<endl;
            return;
      }
      arr[heap_size-1] = data;
      int ind = heap_size-1;
      while(ind>0 && arr[ind].key<arr[(ind-1)/2].key){
            swap(arr[ind], arr[(ind-1)/2]);
            ind = (ind-1)/2;
      }
}

//deleting and return minimum element from heap
template<class T>
T queue_priority<T>::pop(){
      if(heap_size == 0){
            cout<<"LIST IS EMPTY"<<endl;
            return T{ };
      }
      swap(arr[heap_size - 1], arr[0]);
      heap_size--;
      min_heapify(0);
      return arr[heap_size];
}

//return minimum element without deleting it
template<class T>
T queue_priority<T>::top(){
      if(heap_size == 0){
            cout<<"List is empty"<<endl;
            return T{ };
      }
      return arr[0];
}

//sorting the heap
template<class T>
void queue_priority<T>::heap_sort(bool ascending){
      int tmp = heap_size;
      for(int i =0; i<tmp; i++){
            pop();
      }

      heap_size = tmp;
      if(ascending == true){
            for(int i =0; i<heap_size/2; i++){
                  swap(&arr[i], &arr[heap_size-1-i]);
            }
      }
}

//building heap from array
template<class T>
queue_priority<T> build_heap(T arr1[], int n, int capacity){
      queue_priority<T> heap;
      heap.arr = arr1;
      heap.set_heap_size(n);
      heap.set_heap_capacity(capacity);
      for(int i = (n-1)/2; i>=0; i--){
            heap.min_heapify(i);
      }
      return heap;
}
