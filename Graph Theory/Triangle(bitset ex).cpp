#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
const int N=3*1e3+5;
vector<bitset<N>> g(N);
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++){
            int t=s[j]-'0';
            if(t) g[i][j+1]=1;
        }
    }
    ll res=0;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++) if(g[i][k]) {bitset<N> b=g[i]&g[k];res+=b.count();}
    }
    cout << res/6 <<  endl;
    return 0;
}