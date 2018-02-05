#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<std::vector<int> >vvi;

int main(int argc, char const *argv[]) {
      int t;
      cin>>t;
      while(t--){
            int n;
            cin>>n;
            vi time(n);
            vi toll_time(n, 0), orig_toll_time(n, 0);
            cin>>time[0];
            toll_time[0] = time[0];
            int store = time[0];
            int tot_toll = time[0];
            for(int i =1; i<n; i++){
                  cin>>time[i];
                  tot_toll+=time[i];
                    //cout<<store<<endl;
                  if(time[i] > store){
                      store = time[i];
                  }
            }
            int c, d, s;
            cin>>c>>d>>s;
            if(n==1) {
                cout<<'0'<<endl;
                continue;
            }
            float dist_bw_tunnel = d*(n-1);
            //cout<<dist_bw_tunnel<<' '<<n<<' '<<d<<" ";
            float time_first = tot_toll + dist_bw_tunnel/s;
            //float delay = toll_time[n-1] - gain;
            float time_taken = time_first + (c-1)*(time[0]) + (store-time[0]);
            cout<<std::fixed;
            //cout<<setprecision(9)<<store<<' '<<time_first<<' '<<' '<<time_taken - time_first<<endl;
            cout<<setprecision(9)<<time_taken - time_first<<endl;
      }
      return 0;
}
