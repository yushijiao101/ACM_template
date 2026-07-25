#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
struct Node{
    int prv;
    int to;
};
Node node[N];
int vis[N];
void solve() {
    // 优化标准输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    node[1].prv=0;
    node[1].to=100004;
    for(int i=2;i<=n;i++){
    int k,p;
    cin >> k >> p;
    if(p==0){//i插入k左边
        int a=node[k].prv;
        node[a].to=i;
        node[k].prv=i;
        node[i].prv=a;
        node[i].to=k;
    }
        else{//i插入p右边
        int b=node[k].to;
        node[b].prv=i;
        node[k].to=i;
        node[i].to=b;
        node[i].prv=k; 
        }
    }
    int m;
    cin >> m;
    for(int i=1;i<=m;i++){
        int k;
        cin >> k;
        if(vis[k]) continue;
        int a=node[k].prv;
        int b=node[k].to;
        node[a].to=b;
        node[b].prv=a;
        vis[k]=1;
    }
    int t=0;
    while(t!=100004){
        t=node[t].to;
        if(t!=100004) cout<<t<<" ";
    }
}

signed main() {
    solve();
    return 0;
}