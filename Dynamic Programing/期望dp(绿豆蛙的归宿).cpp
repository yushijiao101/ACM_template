#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int N = 1e5 + 10;
int n,m;
vector<vector<pii>> g(N);
int out[N];
void add(int a,int b,int c){
    g[a].push_back({b,c});
}
double dp[N];//dp[i]表示从i到终点的长度期望
//DFN形式 dp[u] += ( dp[v] + w_uv ) * 1/out[u] (u的出度)
double dfs(int u){
    if(dp[u]) return dp[u];
    for(auto [v,w]:g[u]){
        dfs(v);
        dp[u]+=(dp[v]+w)*1.0/out[u]*1.0;
    }
    return dp[u];
}
int main(){
    cin >> n >> m;
    dp[n]=0;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        out[a]++;
    }
    cout << fixed << setprecision(2)<<dfs(1);
    return 0;
}