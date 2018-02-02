#include<bits/stdc++.h>
using namespace std;

class c1{
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
      }
};

int main(int argc, char const *argv[]) {
      c1 obj;
      c1::iterator itr = obj.func1();

}
