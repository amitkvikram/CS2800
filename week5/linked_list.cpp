/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Code: Double Linked List
*/

#include<iostream>
using namespace std;

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
      insert(end(), x);
}

template <class T>
void dll<T>::push_front(T x){
      insert(begin(), x);
}

template <class T>
void dll<T>::pop_back(){
      erase(end().current->prev);
}

template <class T>
void dll<T>::pop_front(){
      erase(begin());
}

template <class T>
const T & dll<T>::front() const{
      return (Head->next)->data;
}

template <class T>
const T & dll<T>::back() const{
      return (Tail->prev)->data;
}
