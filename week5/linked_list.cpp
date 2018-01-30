/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Code: Double Linked List
*/

#include<iostream>
using namespace std;

template <class T>
class dll{
      private:
            class node{
                  public:
                        T data;
                        node *prev = nullptr;
                        node *next = nullptr;
                        node(T &x, node *p, node *q){
                        prev = p;
                        next = q;
                        data = x;
                        }
            };
            int theSize = 0;
            node *Head = nullptr;
            node *Tail = nullptr;

      public:
            void push_back(T x);
            void push_front(T x);
            T front();
            T back();
            void pop_back();
            void pop_front();
            int size();
            bool is_empty();
};

// void dll::push_back(T &x){
//
// }

template <class T>
int dll<T>::size(){
      return theSize;
}

template <class T>
bool dll<T>::is_empty(){
      return size() == 0;
}

template <class T>
void dll<T>::push_back(T x){
      theSize++;
      Tail = new node{x, Tail, nullptr};
      if(Head == nullptr) Head = Tail;
}

int main(){
      char *a = "amit";

      dll<char*> my_list;
      my_list.push_back((char*)"amit");
      cout<<my_list.size()<<endl;
      return 0;
}
