#include<bits/stdc++.h>
using namespace std;
int const inf = 10000;

void print_path(int n, int pred[][100], int a, int b){
    if(a == b){
        cout << a << ' ';
    }
    else if(pred[a][b] == inf){
        cout << "no path found ";
    }
    else{
        print_path(n, pred, a, pred[a][b]);
        cout << b << ' ';
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    int d[n][100];
    int pred[n][100];
    int a, b, wt;
    
    //Initialize distance matrix
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(i==j)
                d[i][j] = 0;
            else
                d[i][j] = inf;
        }
    }

    //take input
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> wt;
        d[a][b] = wt;
    }

    //initialize predecessor matrix
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n; j++){
            if(d[i][j] == inf || i== j)
                pred[i][j] = inf;
            else
                pred[i][j] = i;
        }
    }

    //Floyd Warshall algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    //print distance matrix
    for (int i = 0; i<n; i++){
        for (int j = 0; j < n; j++){
            if(d[i][j] == inf)
                cout << "inf" << ' ';
            else cout << d[i][j] << ' ';
        }
        cout << endl;
    }

    cout<<endl;
    
    //print predecessor matrix
    for(int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            if(pred[i][j] == inf)
                cout << "nil ";
            else cout << pred[i][j] << ' ';
        }
        cout << endl;
    }

    //print path
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a >> b;
        print_path(n, pred, a, b);
        cout << endl;
    }

    return 0;
}