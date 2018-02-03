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
<<<<<<< HEAD

=======
//
>>>>>>> e78f55c2ce8b24b7c44ca161897bbd507fd92e37
// class c1{
// private:
//       int x = 0;
// public:
<<<<<<< HEAD
//       int z = 0;
=======
>>>>>>> e78f55c2ce8b24b7c44ca161897bbd507fd92e37
//       class c2{
//       private:
//             int y;
//       public:
<<<<<<< HEAD
//             // friend class c1;
//             void init1(){
//                   c1 obj3;
//                   obj3.x = 0;
//             }
//       };
//       void init(){
//             c2 obj1;
//             // obj1.y = x;
//             obj1.init1();
//       }
// };

class c1{
private:
      int x = 0;
public:
      class c2{
      public:
            int x1 = 0;
      };

      c1 func1(){
            c2 obj1;
            return {obj1};
      }
};

int main(int argc, char const *argv[]) {
      c1 obj2;
      obj2.func1();
=======
//             friend class c1;
//       };
//       void init(){
//             c2 obj1;
//             obj1.y = 2;
//       }
// };

int main(int argc, char const *argv[]) {
      // c1 obj2;
      // obj2.init();
      std::list<int> v;
      v.push_back(2);
      v.push_back(3);
      v.pop_back();
      v.pop_back();
      std::list<int>::iterator itr;
      itr = v.begin();
      cout<<*itr<<endl;
>>>>>>> e78f55c2ce8b24b7c44ca161897bbd507fd92e37
      return 0;
}
