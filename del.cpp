#include<bits/stdc++.h>
using namespace std;

typedef std::vector<int> vi;
#define rep(i, a, b) for(int i = a; i<b; i++)
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;
#define all(a) (a.begin(), a.end())

class graphNode}
public:
      bool visited = false;
      int parent =-1;
      list<int> adjList;
};

int main(){
      int n, m;
      cin>>n>>m;
      vector<graphNode> v(n);
      int a, b;
      rep(i, 0, m){
            cin>>a>>b;
            a--; b--;
            v[a].adjList.pb(b);
            v[b].adjList.pb(a);
      }

      
}

.
