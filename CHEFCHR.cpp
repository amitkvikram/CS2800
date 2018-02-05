#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<std::vector<int> >vvi;

bool check(vi &v, vi &count){
      bool flag = true;
      for(int i =0; i<26; i++){
            if(count[i]!=v[i]) flag = false;
      }
      return flag;
}

int main(int argc, char const *argv[]) {
      int t;
      cin>>t;
      vi v(26, 0);
      string s = "chef";
      for(int i =0; i<s.size(); i++){
            v[s[i]- 'a']++;
      }
      while(t--){
            string str;
            cin>>str;
            if(str.size()<s.size()){
                  cout<<"normal\n";
                  continue;
            }
            else{
                vi count(26, 0);
                int res =0;
                for(int i =0; i<s.size(); i++){
                      count[str[i]-'a']++;
                }
                if(check(v, count)) res++;
                for(int i = s.size(); i<str.size(); i++){
                      count[str[i-s.size()]-'a']--;
                      count[str[i]-'a']++;
                      if(check(v, count)) res++;
                }

                if(res>0) cout<<"lovely "<<res<<endl;
                else cout<<"normal\n";
            }
      }
      return 0;
}
