#include <bits/stdc++.h>
using namespace std;
int n;
const int N=105;
vector<bitset<105>> g(N);
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int t;
            cin >> t;
            if(t) g[i][j]=1;
            else g[i][j]=0;
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++) if(g[i][k]) g[i]|=g[k];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}