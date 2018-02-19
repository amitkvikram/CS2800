#include<iostream>
using namespace std;

class c1{
public:
      int y =10;
      class a{
            public:
                  int b;
      };
      class c2{
            private:
                  int v = 10;
            public:
            int x = 20;
            void func1(){
                  cout<<y<<endl;
            }
            friend class c1;
      };
};

int main(){
      c1 obj1;
      obj1.v = 30;
      c1::c2 obj2;
      obj2.func1();
      //cout<<obj2.y;
}
