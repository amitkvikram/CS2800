#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef std::vector<float> vi;

int main(int argc, char const *argv[]) {
      int t;
      cin>>t;
      while(t--){
            int n;
            cin>>n;
            vi time(n);
            int max = 0;
            for(int i =0; i<n; i++){
                  cin>>time[i];
                  if(time[i]>=max) max = time[i];
            }
            int c, d, s;
            cin>>c>>d>>s;
            //cout<<std::fixed;
            printf("%.9f\n", (float)(max*(c-1)));
      }
      return 0;
}
