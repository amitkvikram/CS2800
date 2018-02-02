#include <bits/stdc++.h>
using namespace std;

//
//
//
// class C{
// private:
//       int x;
//       int y;
// public:
//       void operator*(int m){
//             x = x+m;
//             y = y*m;
//             cout<<x<<' '<<y<<endl;
//       }
//       C(int a, int b){
//             x = a;
//             y = b;
//             cout<<x<<' '<<y<<endl;
//       }
//       friend void operator*(int m, C t);
// };
//
// void operator*(int m,C t){
//       t.x = t.x*m;
//       t.y = t.y+m;
//       cout<<t.x<<' '<<t.y<<endl;
// }

class c1{
private:
      int x = 0;
public:
      class c2{
      private:
            int y;
      public:
            friend class c1;
      };
      void init(){
            c2 obj1;
            obj1.y = 2;
      }
};

int main(int argc, char const *argv[]) {
      c1 obj2;
      obj2.init();
      return 0;
}
