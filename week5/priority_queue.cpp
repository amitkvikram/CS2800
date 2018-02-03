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
      data_type *arr;                     //pointer to array in which elemnts of heap are stored
      void min_heapify(int i);      //function to min_heapify at vertex i
      int left_child(int i);        //function to return left child of ith node
      int right_child(int i);       //function to store right child of ith node
      void print_heap();            //function to print heap
      void insert_element(T data);      //function to insert an element in heap
      T delete_min();             //function to delete minimum element from heap
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

void swap(data_type *a, data_type *b){          //function to swap two elements a and b
      data_type temp = *a;
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
void queue_priority<T>::insert_element(T data){
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
T queue_priority<T>::delete_min(){
      if(heap_size == 0){
            cout<<"LIST IS EMPTY"<<endl;
            return T{ };
      }
      swap(arr[heap_size - 1], arr[0]);
      heap_size--;
      min_heapify(0);
      return arr[heap_size];
}

//sorting the heap
template<class T>
void queue_priority<T>::heap_sort(bool ascending){
      int tmp = heap_size;
      for(int i =0; i<tmp; i++){
            delete_min();
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

//decrease key
template<class T>
void queue_priority<T>::decrease_key(int ind, int new_key){
      arr[ind].key = new_key;
      while(ind>0 && arr[ind].key<arr[(ind-1)/2].key){
            swap(arr[ind], arr[ind-1]/2);
            ind = (ind - 1)/2;
      }
}

//printing heap
template<class T>
void queue_priority<T>::print_heap(){
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
                  printf("%03d",arr[ind].key);
                  ind++;
                  for(int i =0; i<mid_gap; i++){
                        cout<<"   ";
                  }
            }
            cout<<endl;
      }
      cout<<endl;
}

//main begins here
int main() {
      int n;
      cout<<"Enter Number of Elements: ";
      cin>>n;
      data_type *arr = new data_type[100];
      int a, b;
      cout<<"Enter "<<n<<" Elements: ";
      for(int i =0; i<n; i++){
            cin>>a>>b;
            arr[i].edge_index = a;
            arr[i].key = b;
      }
      queue_priority<data_type> heap = build_heap(arr, n, 100);
      int choice;
      data_type tmp;
      do{
            cout<<"------------------------------------------------------------------\n";
            cout<<"Enter 1 to insert an element in heap"<<endl;
            cout<<"Enter 2 to delete min element from heap"<<endl;
            cout<<"Enter 3 to sort the array(heap)"<<endl;
            cout<<"Enter 4 to print heap"<<endl;
            cout<<"Enter 5 for decreasing key\n";
            cout<<"Enter 6 to exit"<<endl;
            cout<<"Enter Your Choice: ";
            cin>>choice;
            switch(choice) {
                  case 1:
                        cout<<"Enter Element to  be Inserted: ";
                        cin>>a>>b;
                        heap.insert_element({a, b});
                        break;
                  case 2:
                        tmp = heap.delete_min();
                        cout<<"Minimum Element: "<<tmp.index<<' '<<tmp.key<<endl;
                        break;
                  case 3:
                        heap.heap_sort(true);
                        cout<<"Array is sorted"<<endl;
                        break;
                  case 4:
                        heap.print_heap();
                        break;
                  case 5:
                        cout<<
                  case 6:
                        cout<<"Exiting"<<endl;
                        break;
                  default:
                        cout<<"Unknown Choice   ....Exiting"<<endl;
            }
      }while(choice<5);
      return 0;
}
//main ends here
