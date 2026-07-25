#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
const int L = 20;

int n;
int dfn[N], depth[N];
int fa[N][L];
vector<int> G[N];       // 原树
vector<int> vr[N];  // 虚树
void add(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
}

int tot = 0; 
void dfs(int u, int p) {
    dfn[u] = ++tot;
    depth[u] = depth[p] + 1;
    fa[u][0] = p;
    
    // 预处理倍增数组
    for (int k = 1; k < L; k++) {
        fa[u][k] = fa[fa[u][k-1]][k-1];
    }
    
    for (auto v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int k = L - 1; k >= 0; k--) {
        if (depth[u] - (1 << k) >= depth[v]) {
            u = fa[u][k];
        }
    }
    if (u == v) return u;
    for (int k = L - 1; k >= 0; k--) {
        if (fa[u][k] != fa[v][k]) {
            u = fa[u][k];
            v = fa[v][k];
        }
    }
    return fa[u][0];
}
int key[N];//记录关键点
int cost[N];//以这个节点为根的子树满足不连通条件 最少需要多少步
int flag[N];//以这个节点为根的子树还有能向上连接的key点
//我们要记录这个点是不是关键点
int build(vector<int>& h) {
    sort(h.begin(), h.end(), [](int a, int b) {
        return dfn[a] < dfn[b];
    });
    int k = h.size();
    for(int i=0;i<k;i++) if(key[fa[h[i]][0]]) return -1;
    for (int i = 0; i < k - 1; i++) {
        h.push_back(lca(h[i], h[i + 1]));
    }
    // h.push_back(1); 
    sort(h.begin(), h.end(), [](int a, int b) {
        return dfn[a] < dfn[b];
    });
    h.erase(unique(h.begin(), h.end()), h.end());
    // 4. 清空本次需要用到的虚树节点的边
    for (int u : h) {
        vr[u].clear();
        flag[u]=0;
        cost[u]=0;
    }
    
    for (int i = 1; i < h.size(); i++) {
        int p = lca(h[i - 1], h[i]);
        vr[p].push_back(h[i]);
    }
    return h[0];
}
void DP(int u){
    int sum=0;
    for(auto v:vr[u]){
        DP(v);
        sum+=flag[v];
        cost[u]+=cost[v];
    }
    if(!key[u]){//如果u不是关键点
        if(sum>1) {cost[u]++;flag[u]=0;}
        else flag[u]=sum;
    }
    else{//如果u是关键点
        cost[u]+=sum;//把下面的每个都堵死
        flag[u]=1;
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    // 0 号点作为边界，深度为 0
    depth[0] = 0; 
    dfs(1, 0);
    int q;
    cin >> q;
    while(q--){
        int t; cin >> t;
        vector<int> k(t);
        for(int i=0;i<t;i++) {cin >> k[i];key[k[i]]=1;} 
        vector<int> temp=k;
        int root=build(k);
        if(root==-1) cout << -1 << endl;
        else{
        DP(root);
        cout << cost[root] << endl;
        }
        for(int i=0;i<t;i++) key[temp[i]]=0;
    }
    return 0;
}