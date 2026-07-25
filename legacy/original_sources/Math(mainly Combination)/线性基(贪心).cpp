#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int p[64];

void insert(int x){
    for(int i=63;i>=0;i--){
        if(x>>i&1){//如果x的第i位是1
            if(p[i]) x^=p[i];    //p[i]已经存在
            else {p[i]=x;break;}
        }
    }
}

signed main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        insert(x);
    }
        int mx=0;
        for(int i=63;i>=0;i--){
            if((mx^p[i])<mx) continue;
            else mx=mx^p[i];
        }
    cout<<mx;
}