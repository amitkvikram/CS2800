#include<bits/stdc++.h>
#include "linked_list.h"
using namespace std;

class c1{
<<<<<<< HEAD
      int y;
public:
      c1(int x){
            y = x;
=======
private:
      class node{
            public:
                  // T data;
                  // node *prev = nullptr;
                  // node *next = nullptr;
                  // node(T &x, node *p, node *q){
                  // prev = p;
                  // next = q;
                  // data = x;
                  // }
                  int x = 10;
      };
      node Head;
public:
      class iterator{
            private:
                  int x;
            public:
                  friend class c1;
                  iterator(){
                        // current = p;
                  }
      };
public:
      iterator func1(){
            return {};
>>>>>>> e78f55c2ce8b24b7c44ca161897bbd507fd92e37
      }
};

int main(int argc, char const *argv[]) {
<<<<<<< HEAD
      c1 obj1{2};
      dll<int> my_list;
      my_list.push_back(20);
      my_list.push_back(21);

      cout<<my_list.front()<<endl;
=======
      c1 obj;
      c1::iterator itr = obj.func1();

>>>>>>> e78f55c2ce8b24b7c44ca161897bbd507fd92e37
}
