/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Code: Double Linked List
*/

#include<iostream>
using namespace std;

template <class T>
class my_stack{
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
            my_stack(){
                  theSize = 0;
                  Head = new node;
                  Tail = new node;
                  Head->next = Tail;
                  Tail->prev = Head;
            }

            //destructor
            ~my_stack(){
                  clear();
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
                        //friend class dll<T>;
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

                        friend class my_stack<T>;
            };
      public:
            void push(T x);
            const T & top() const;
            void pop();
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
            void clear(){
                  while(theSize!=0){
                        pop();
                  }
            }
};


template <class T>
int my_stack<T>::size(){
      return theSize;
}

template <class T>
bool my_stack<T>::is_empty(){
      return size() == 0;
}

template <class T>
void my_stack<T>::push(T x){
      insert(begin(), x);
}

template <class T>
void my_stack<T>::pop(){
      erase(begin());
}

template <class T>
const T & my_stack<T>::top() const{
      return (Head->next)->data;
}

void print_stack(my_stack<int> &st){
      while(!st.is_empty()){
            cout<<st.top()<<endl;
            st.pop();
      }
}
