#include <bits/stdc++.h>
using namespace std;
const int N = 5*1e5 + 10;
int n;
int w[N];
vector<int> e[N];
int fa[N], dep[N], sz[N], son[N], top[N], id[N], new_w[N], cnt;
// fa: 父节点，dep: 深度，
//sz: 子树大小，son: 重儿子，top: 重链顶节点，id: 线段树编号，new_w: 线段树值
void dfs1(int u,int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    for (auto v : e[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}
void dfs2(int u,int t) {
    top[u] = t;//重链顶节点
    // id[u] = ++cnt;
    // new_w[cnt] = w[u];
    if(!son[u]) return;
    dfs2(son[u], t);
    for(auto v : e[u]){
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);//搜轻儿子
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
int main(){
    cin >> n;
    int m,s;
    cin >> m >> s;
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1(s,-1);
    dfs2(s,s);
    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        cout<<lca(a,b)<<endl;
    }
    return 0;
}