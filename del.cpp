#include<bits/stdc++.h>
using namespace std;

typedef std::vector<int> vi;
#define rep(i, a, b) for(int i = a; i<b; i++)
#define pb push_back

int main(){
      int n, flag, Sum = 0;
      cin>>n;
      vi v(n);
      vi tmp;
      rep(i, 0, n){
            cin>>v[i];
            flag =  0;
            for(auto j:tmp){
                  if(j == v[i]) flag =1 ;
            }
            if(flag == 0) tmp.pb(v[i]);
      }

      sort(tmp.begin(), tmp.end());
      if(tmp.back() - tmp.front()<2){
            cout<<n<<endl;
            for(auto i:v){
                  cout<<i<<' ';
            }
      }

      else{
            vi cnt(3, 0);
            int a = tmp.front(), c = tmp.back(), b = (a+c)/2;
            for(auto i:v){
                  if(i == a) cnt[0]++;
                  else if(i == b) cnt[1]++;
                  else cnt[2]++;
            }

            int min_cnt = min(cnt[0], cnt[2]);
            // int max_cnt = max(2*min_cnt, cnt[1]);
            cout<<n-2*min_cnt<<endl;
            int min_cnt1 = min_cnt;
            rep(i, 0, n){
                  if(v[i] == b) cout<<b<<' ';
                  else if(v[i] == a && min_cnt-->0) cout<<b<<" ";
                  else if(v[i] == c && min_cnt1-->0) cout<<b<<" ";
                  else cout<<v[i]<<' ';
            }
      }
}
