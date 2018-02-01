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
            const T & front() const;
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

template <class T>
void dll<T>::push_front(T x){
      theSize++;
      node *temp = Head;
      Head = new node{x, nullptr, Head};
      if(temp!=nullptr) temp-prev = Head;
}

template <class T>
void dll<T>::pop_back(){
      if(theSize == 0) return;
      theSize--;
      node *temp = Tail;
      Tail = Tail->prev;
      delete temp;
}

template <class T>
void dll<T>::pop_front(){
      if(theSize == 0) return;
      theSize--;
      node *temp = Head;
      Head = Head->
}

template <class T>
const T & dll<T>::front() const{
      if(Head == nullptr) return nullptr;
      return Head->data;
}

template <class T>
const T & dll<T>::back() const{
      if(Head== nullptr) return nullptr;
      return Tail->data;
}

template <class T>
void dll<T>::print(){

}

int main(){
      dll<int> my_list;
      int choice, tmp;
      do{
            cout<<"======================MENU==================\n";
            cout<<"1. Insert at front"<<endl;
            cout<<"2. Insert at end"<<endl;
            cout<<"3. Access last element"<<endl;
            cout<<"4. Access First Element"<<endl;
            cout<<"5. delete last element"<<endl;
            cout<<"6. Delete First Element"<<endl;
            cout<<"7. Access and Delete Last Element"<<endl;
            cout<<"8. Access and Delete First Element"<<endl;
            cout<<"Enter Your Choice: ";
            cin>>choice;
            switch(choice){
                  case 1:
                        cout<<"Enter element: ";
                        cin>>tmp;
                        my_list.push_front(tmp);
                  case 2:
                        cout<<"Enter element: ";
                        cin>>tmp;
                        my_list.push_back(tmp);
                  case 3:
                        cout<<my_list.back();
                  case 4:
                        cout<<my_list.fornt();
                  case 5:
                        my_list.pop_back();
                  case 6:
                        my_list.pop_front();
                  case 7:
                        cout<<my_list.back();
                        my_list.pop_back();
                  case 8:
                        cout<<my_list.front()
                        my_list.pop_front();
            }while(choice<9);
      }


      return 0;
}
