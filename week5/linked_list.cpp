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
            int theSize = 0;

      public:
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
            node *Head = nullptr;
            node *Tail = nullptr;
            void merge_sort(node *a, node *b);
            void split(node *a, node *b, node **firstRef, node **secondRef);
            void merge(node *a1, node *b1, node *a2, node *b2);
            void push_back(T x);
            void push_front(T x);
            const T & front() const;
            const T & back() const;
            void pop_back();
            void pop_front();
            int size();
            bool is_empty();
            node *begin(){
                  return Head;
            }
            node *end(){
                  return Tail;
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
      theSize++;
      node *temp = Tail;
      Tail = new node{x, Tail, nullptr};
      if(Head == nullptr) Head = Tail;
      else temp->next = Tail;
}

template <class T>
void dll<T>::push_front(T x){
      theSize++;
      node *temp = Head;
      Head = new node{x, nullptr, Head};
      if(temp!=nullptr) temp->prev = Head;
      if(Tail == nullptr) Tail = Head;
}

template <class T>
void dll<T>::pop_back(){
      if(theSize == 0) return;
      theSize--;
      node *temp = Tail;
      Tail = Tail->prev;
      if(Tail!=nullptr) Tail->next = nullptr;         //if list had 2 elemnts
      if(Tail == nullptr) Head = Tail;
      delete temp;
}

template <class T>
void dll<T>::pop_front(){
      if(theSize == 0) return;
      theSize--;
      node *temp = Head;
      if(Head->next!=nullptr) Head->next->prev = nullptr;
      Head = Head->next;
      if(Head==nullptr) Tail = nullptr;
      delete temp;
}

template <class T>
const T & dll<T>::front() const{
      if(Head == nullptr){
            static const T invalid = T();
            return invalid;
      }
      return Head->data;
}

template <class T>
const T & dll<T>::back() const{
      if(Head == nullptr){
            static const T invalid = T();
            return invalid;
      }
      return Tail->data;
}

template <class T>
void dll<T>::merge_sort(node *a, node *b){
      node* end1  ;
      node *start2;
      split(a, b, &end1, &start2);
      merge_sort(a, end1);
      merge_sort(b, start2);
      merge(a, end1, start2, b);
}


template <class T>
void dll<T>::sort(){
      merge_sort(Head, Tail);
}

//If number of nodes is odd extra node goes in second part
template <class T>
void dll<T>::split(node *a, node *b, node **firstRef, node **secondRef){
      firstRef = nullptr;
      while(a!=b){
            a = a->next;
            if(a!=b) b = b->prev;
      }
      if(a) *firstRef = a->prev;
      *secondRef = a;
}

template <class T>
void dll<T>::merge(node *a1, node *b1, node *a2, node *b2){
      node *t1 = a1, t2 = a2;
      dll<int> L;
      dll<int> R;
      if(a1 == nullptr || a2 == nullptr){
            return;
      }

      do{
            L.push_back(t1->data);
            t1 = t1->next;
      }while(t1!=b1);

      do{
            R.push_back(t2->data);
            t2 = t2->next;
      }while(t2!=b2);

      t1 = L.begin();
      t2 = R.begin();

      while(t1!=nullptr && t2!=nullptr){
            if(t1->data > t2->data){
                  a1->data = t1->data;
                  t1 = t1->next;
            }
            else{
                  a1->data = t2->data;
                  t2 = t2->next;
            }
            a1 = a1->next;
      }

      while(t1){
            a1->data = t1->data;
            a1=a1->next;
            t1 = t1->next;
      }
      while(t2){
            a1->data = t2->data;
            a2 = a2->next;
            t2 = t2->next;
      }
}

// template <class T>
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
                        break;
                  case 2:
                        cout<<"Enter element: ";
                        cin>>tmp;
                        my_list.push_back(tmp);
                        break;
                  case 3:
                        cout<<my_list.back()<<endl;
                        break;
                  case 4:
                        cout<<my_list.front()<<endl;
                        break;
                  case 5:
                        my_list.pop_back();
                        break;
                  case 6:
                        my_list.pop_front();
                        break;
                  case 7:
                        cout<<my_list.back()<<endl;
                        my_list.pop_back();
                        break;
                  case 8:
                        cout<<my_list.front()<<endl;
                        my_list.pop_front();
                  case 9:
                        my_list.sort();
                        break;
                  case 10:
                        dll<int>::node *temp = my_list.begin();
                        while(temp!=nullptr){
                              cout<<temp->data<<' ';
                              temp = temp->next;
                        }
                        cout<<endl;
            }
      }while(choice<11);

      return 0;
}
