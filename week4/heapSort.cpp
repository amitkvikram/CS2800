/*
	Name: Amit Vikram Singh
	Roll No: 111601001
	Date: 30/01/2018
	Problem Name: Heap
*/
#include<bits/stdc++.h>
using namespace std;

class Heap{                         //class for heap
private:
      int heap_capacity;            //variable to store capacity of heap
      int heap_size;                //size of heap
public:
      int *arr;                     //pointer to array in which elemnts of heap are stored
      void min_heapify(int i);      //function to min_heapify at vertex i
      int left_child(int i);        //function to return left child of ith node
      int right_child(int i);       //function to store right child of ith node
      // int operator[](int index);
      void print_heap();            //function to print heap
      void insert_element(int data);      //function to insert an element in heap
      int delete_min();             //function to delete minimum element from heap
      void heap_sort();             //function to sort the heap
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

void swap(int *a, int *b){          //function to swap two elements a and b
      int temp = *a;
      *a = *b;
      *b = temp;
}

int Heap::left_child(int i){
      return 2*i+1;
}

int Heap::right_child(int i){
      return 2*i+2;
}

void Heap::min_heapify(int i){
      int smallest_index = i;
      int lchild = left_child(i);
      int rchild = right_child(i);
      if(lchild < heap_size && arr[lchild] < arr[smallest_index]){
            smallest_index = lchild;
      }
      if(rchild < heap_size && arr[rchild] < arr[smallest_index]){
            smallest_index = rchild;
      }

      if(smallest_index != i){
            swap(arr[smallest_index], arr[i]);
            min_heapify(smallest_index);
      }
}

//Inserting element in heap
void Heap::insert_element(int data){
      heap_size++;
      if(heap_size > heap_capacity){
            cout<<"Heap exceeding its capacity, returning without inserting"<<endl;
            return;
      }
      arr[heap_size-1] = data;
      int ind = heap_size-1;
      while(ind>0 && arr[ind]<arr[(ind-1)/2]){
            swap(arr[ind], arr[(ind-1)/2]);
            ind = (ind-1)/2;
      }
}

//deleting minimum element from heap
int Heap::delete_min(){
      if(heap_size == 0){
            cout<<"LIST IS EMPTY"<<endl;
            return INT_MAX;
      }
      swap(arr[heap_size - 1], arr[0]);
      heap_size--;
      min_heapify(0);
      return arr[heap_size];
}

//printing heap
void Heap::print_heap(){
      int height = (int) (log(heap_size)/log(2) + 1);
      int tmp = heap_size;

      int numNode_lastLevel = pow(2, height -1);
      // cout<<"Height = "<<height<<' '<<numNode_lastLevel<<endl;
      int ind = 0, flag = 0, count = 0, initial_gap, num_node, mid_gap;
      for(int i =0; i<height; i++){
            initial_gap = (int)(pow(2, max(height-i-1, 0))) - 1;
            mid_gap = pow(2, max(height - i, 0)) - 1;
            num_node = (int) pow(2, i);
            if(i==height-1) initial_gap = 0;
            for(int j =0; j<initial_gap; j++){
                  cout<<"   ";
            }
            for(int i =0; i<num_node && ind<heap_size; i++){
                  printf("%03d",arr[ind]);
                  // cout<<arr[ind]<<" ";
                  ind++;
                  for(int i =0; i<mid_gap; i++){
                        cout<<"   ";
                  }
            }
            cout<<endl;
      }
      cout<<endl;
}

//sorting the heap
void Heap::heap_sort(){
      int *temp_arr = new int[heap_size];
      if(temp_arr == NULL){
            cout<<"Error in Memory Allocation(@heap sort)"<<endl;
            return;
      }
      int tmp = heap_size;
      for(int i =0; i<tmp; i++){
            temp_arr[i] = delete_min();
            //print_heap();
            //cout<<temp_arr[i]<<endl;
      }
      for(int i =0; i<tmp; i++){
            arr[i] = temp_arr[i];
      }
      heap_size = tmp;
      delete [] temp_arr;
}

//building heap from array
Heap build_heap(int arr1[], int n, int capacity){
      Heap heap;
      heap.arr = arr1;
      //cout<<"heap initialized"<<endl;
      heap.set_heap_size(n);
      heap.set_heap_capacity(capacity);
      for(int i = (n-1)/2; i>=0; i--){
            heap.min_heapify(i);
      }
      return heap;
}

//main begins here
int main() {
      int n;
      cout<<"Enter Number of Elements: ";
      cin>>n;
      int arr[100];
      cout<<"Enter "<<n<<" Elements: ";
      for(int i =0; i<n; i++){
            cin>>arr[i];
      }
      Heap heap = build_heap(arr, n, 100);
      int choice, tmp;
      do{
            cout<<"------------------------------------------------------------------\n";
            cout<<"Enter 1 to insert an element in heap"<<endl;
            cout<<"Enter 2 to delete min element from heap"<<endl;
            cout<<"Enter 3 to sort the array(heap)"<<endl;
            cout<<"Enter 4 to print heap"<<endl;
            cout<<"Enter 5 to exit"<<endl;
            cout<<"Enter Your Choice: ";
            cin>>choice;
            switch(choice) {
                  case 1:
                        cout<<"Enter Element to  be Inserted: ";
                        cin>>tmp;
                        heap.insert_element(tmp);
                        break;
                  case 2:
                        tmp = heap.delete_min();
                        if(tmp!=INT_MAX) cout<<"Minimum Element: "<<tmp<<endl;
                        break;
                  case 3:
                        heap.heap_sort();
                        cout<<"Array is sorted"<<endl;
                        break;
                  case 4:
                        heap.print_heap();
                        break;
                  case 5:
                        cout<<"Exiting"<<endl;
                        break;
                  default:
                        cout<<"Unknown Choice   ....Exiting"<<endl;
            }
      }while(choice<5);
      return 0;
}
//main ends here
