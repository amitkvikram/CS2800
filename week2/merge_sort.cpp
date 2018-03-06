#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i =a; i<b; i++)

//Inertevals l<=i<=mid  mid+1<=i<=r
void merge(auto &v, int l, int mid, int r){
      vector<int> tmp1((mid-l+1));
      vector<int> tmp2((r-mid));
      rep(i, 0, mid-l+1){
            tmp1[i] = v[l+i];
      }
      rep(i, 0, r-mid){
            tmp2[i] = v[mid+1+i];
      }
      int i = 0, j = 0, ind  = l;
      while(i<=(mid-l) && j<=(r-mid-1)){
            if(tmp1[i]<tmp2[j]){
                  v[ind] = tmp1[i];
                  i++;
                  ind++;
            }
            else{
                  v[ind] = tmp2[j];
                  j++;
                  ind++;
            }
      }
      while(i<=(mid-l)){
            v[ind] = tmp1[i];
            ind++; i++;
      }

      while(j<=(r-mid-1)){
            v[ind] = tmp2[j];
            ind++; j++;
      }
}

void mergeSort(auto &v, int l, int r){
      if(l>=r) return;
      int mid = (l+r)/2;
      mergeSort(v, l, mid);
      mergeSort(v, mid+1, r);
      merge(v, l, mid, r);
}

int main(){
      int n;
      cin>>n;
      std::vector<int> v(n);
      rep(i, 0, n){
            cin>>v[i];
      }
      mergeSort(v, 0, n-1);
      rep(i, 0, n){
            cout<<v[i]<<' ';
      }
}
