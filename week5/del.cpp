#include<bits/stdc++.h>
#include "linked_list.h"
using namespace std;

class c1{
public:
      int x;
      int y;
      c1(int a, int b){
            x = a;
            y = b;
      }
      const c1 & foo() {
            return *this;
            // return 10;
      }
};
int main(int argc, char const *argv[]) {
      c1 obj1{1,2};
      obj1 = {2,3};
      c1 *a = &(obj1.foo());
      (*a).x = 10;
      cout<<obj1.x<<endl;
      // const int a = obj1.foo();
      // a = 20;
}
