/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Code: Double Linked List
*/

#ifndef dll_H
#define dll_H

#include<iostream>
using namespace std;

template <class T>
class dll{
      private:
            int theSize;
            class node{
                  public:
                        T data;
                        node *prev = nullptr;
                        node *next = nullptr;
                        node(const T &x = T{ }, node *p = nullptr, node *q = nullptr){
                        prev = p;
                        next = q;
                        data = x;
                        }
            };
            node *Head;
            node *Tail;
      public:
            //Constructor
            dll(){
                  theSize = 0;
                  Head = new node;
                  Tail = new node;
                  Head->next = Tail;
                  Tail->prev = Head;
            }

            //destructor
            ~dll(){
                  // clear();
                  delete Head;
                  delete Tail;
            }
      public:
            class const_iterator{
                  protected:
                        node *current;
                        const_iterator( node *p ) : current{ p }
                        { }
                  public:
                        friend class dll<T>;
                        const_iterator( ) : current{ nullptr }
                        { }

            };
            class iterator : public const_iterator{
                  public:
                        iterator(){ };

                        iterator operator++(int){
                              iterator old = *this;
                              this->current = this->current->next;
                              return old;
                        }

                        bool operator==(iterator itr){
                              return this->current ==  itr.current;
                        }

                        bool operator!=(iterator temp){
                              return !(temp == *this);
                        }

                        const T & operator*() const{
                              return this->current->data;
                        }

                  protected:
                         iterator(node *p) : const_iterator{ p }
                        { }

                        friend class dll<T>;
            };
      public:
            void push_back(T x);
            void push_front(T x);
            const T & front() const;
            const T & back() const;
            void pop_back();
            void pop_front();
            int size();
            bool is_empty();

            iterator begin(){
                  return {Head->next};
            }
            iterator end(){
                  return {Tail};
            }

            const_iterator begin() const{
                  return {Head->next};
            }
            const_iterator end() const{
                  return {Tail};
            }
            //insert x befot itr(as done in STL)
            void insert(iterator itr, T x){
                  theSize++;
                  node *temp = new node{x, itr.current->prev ,itr.current };
                  itr.current->prev->next = temp;
                  itr.current->prev = temp;
            }

            //erase element pointed by itr(following STL implementation)
            void erase(iterator itr){
                  theSize--;
                  itr.current->next->prev = itr.current->prev;
                  itr.current->prev->next = itr.current->next;
                  delete itr.current;
            }
            void sort();
};


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

#endif
