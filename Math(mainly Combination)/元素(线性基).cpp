#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
int n;
int p[64];
int ans=0;
void insert(int x,int val){
    for(int i=63;i>=0;i--){
        if(x>>i&1){//如果x的第i位是1
            if(p[i]) x^=p[i];    //p[i]已经存在
            else {p[i]=x;ans+=val;break;}
        }
    }
}
vector<pii> v;
signed main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        int x,val;cin >> x >> val;
        v.push_back({x,val});
    }
    sort(v.begin(),v.begin()+n,[](const pii &a,const pii &b){
        return a.second>b.second;
    });
    for(int i=0;i<n;i++){
        auto [x,val] = v[i];
        insert(x,val);
    }
    cout<<ans;
}