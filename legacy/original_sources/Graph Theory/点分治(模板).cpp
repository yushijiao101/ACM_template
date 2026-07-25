#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node 
{
    ll nx;
    ll weight;
};
vector<ll> dict(1e7+2,0);
vector<ll> subtree_size;
vector<vector<Node>> adj; 
vector<bool> vis; // 记录遍历过的重心
ll n;//节点数
ll m;
vector<ll> sz;
vector<ll> selected_nodes;
int q[10000005], q_ptr;
bool has[10000005];
ll getSize(ll u,ll p) {//每个节点子树大小 同时计算连通块大小
    sz[u] = 1;
    for (auto& edge : adj[u]) {
        ll v = edge.nx;
        if (v == p || vis[v]) continue; 
        sz[u] += getSize(v, u);
    }
    return sz[u];
}
ll findRoot(ll u, ll p, ll total) {//寻找重心
    for (auto& edge : adj[u]) {
        ll v = edge.nx;
        if (v == p || vis[v]) continue;
        if (sz[v] > total / 2) {
            return findRoot(v, u, total); 
        }
    }
    return u; 
}
void getdist(ll u,ll p,ll sum,vector<ll>& cur){
    if(sum>1e7) return;
    cur.push_back(sum);
    for(int i=1;i<=m;i++) if(selected_nodes[i]>=sum&&has[selected_nodes[i]-sum]) dict[i]=1;
    for(auto& edge:adj[u]){
        ll v=edge.nx;
        if(v==p||vis[v]) continue;
        getdist(v,u,sum+edge.weight,cur);
    }
}
void calc(ll u) {//求解关于重心的答案
    q_ptr=0;
    for(auto& it : adj[u]) {
        if(vis[it.nx]) continue;
        vector<ll> cur;
        getdist(it.nx, u, it.weight, cur);
        for(auto it:cur) {q[++q_ptr]=it; has[it]=true;}
    }
    for(int i=1;i<=q_ptr;i++) has[q[i]]=false;
    return;
}
void solve(ll u){
    ll size = getSize(u, 0);
    ll cenxroid = findRoot(u, 0, size);
    vis[cenxroid] = true;
    calc(cenxroid); // 计算以 cenxroid 为根的子树问题
    // 在这里处理以 cenxroid 为根的子树问题
    for (Node v : adj[cenxroid]) {
        if (vis[v.nx]) continue;
        solve(v.nx); // 计算以 v 为根的子树问题
    }
   return;
}
void dfs(ll u, ll p) {
    subtree_size[u] = 1;
        for (Node v : adj[u]) {
            if (v.nx == p|| vis[v.nx]) continue;
            dfs(v.nx, u);
            subtree_size[u] += subtree_size[v.nx];
        }
}

int main() {
    has[0]=true;
    cin >> n >> m;
    adj.resize(n + 1);
    sz.resize(n + 1, 0);
    vis.resize(n + 1, false);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    selected_nodes.resize(m+1,0);
    int cnt=0;
    for(int i=1;i<=m;i++){
        int k;
        cin >> k;
        selected_nodes[++cnt]=k;
    }
        subtree_size.resize(n + 1, 0);
    dfs(1, 0);
    solve(1);
    for(int i=1;i<=m;i++){
        if(dict[i]) cout<<"AYE"<<endl; 
        else cout<<"NAY"<<endl;
    }
    return 0;
}