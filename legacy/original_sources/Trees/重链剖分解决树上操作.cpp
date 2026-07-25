#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
const int N = 5*1e5 + 10;
int P;
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
    id[u] = ++cnt;
    new_w[cnt] = w[u];
    if(!son[u]) return;
    dfs2(son[u], t);
    for(auto v : e[u]){
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);//搜轻儿子
    }
}
struct Node {
    ll sum;  // 存储区间和
    ll add;  // 存储加法懒标记
    // 如果有区间修改，可以再加个 ll setVal 和 bool hasSet
} tree[N << 2]; // 直接开4倍数组，比 vector 快且简洁
ll a[N]; // 原数组
// 辅助函数：计算子节点编号
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }

// 向上更新：用儿子更新父亲
void push_up(int p) {
    tree[p].sum = tree[ls(p)].sum + tree[rs(p)].sum;
}

// 向下更新：把懒标记传给儿子
void push_down(int p, int l, int r) {
    if (tree[p].add != 0) {
        int mid = (l + r) >> 1;
        
        // 处理左儿子
        tree[ls(p)].add += tree[p].add;
        tree[ls(p)].sum += tree[p].add * (mid - l + 1);
        
        // 处理右儿子
        tree[rs(p)].add += tree[p].add;
        tree[rs(p)].sum += tree[p].add * (r - mid);
        
        // 清空父节点标记
        tree[p].add = 0;
    }
}

// 建树
void build(int p, int l, int r) {
    tree[p].add = 0;
    if (l == r) {
        tree[p].sum = new_w[l]; 
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}

// 区间加法：[ql, qr] 是目标，[l, r] 是当前
void update(int p, int l, int r, int ql, int qr, ll val) {
    // 1. 目标区间完全包含当前区间
    if (ql <= l && r <= qr) {
        tree[p].sum += val * (r - l + 1);
        tree[p].add += val;
        return;
    }
    // 2. 否则，先下放标记，再递归
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ls(p), l, mid, ql, qr, val);
    if (qr > mid)  update(rs(p), mid + 1, r, ql, qr, val);
    push_up(p);
}
void update_path(int x, int y, ll val) {
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(1, 1, n, id[top[x]], id[x], val);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    update(1, 1, n, id[y], id[x], val);
}
void update_tree(int x, ll val) {
    update(1, 1, n, id[x], id[x]+sz[x]-1, val);
}
// 区间查询
ll query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p].sum%P;
    
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += query(ls(p), l, mid, ql, qr)%P;
    if (qr > mid)  res += query(rs(p), mid + 1, r, ql, qr)%P;
    return res%P;
}
ll query_path(int x, int y) {
    ll res = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res += query(1, 1, n, id[top[x]], id[x]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    res += query(1, 1, n, id[y], id[x])%P;
    return res%P;
}
ll query_tree(int x) {
    return query(1, 1, n, id[x], id[x]+sz[x]-1);
}
int main(){
    cin >> n;
    int m,r;
    cin >> m >> r >> P;
    for(int i=1;i<=n;i++) cin >> w[i];
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1(r,-1);
    dfs2(r,r);
    build(1, 1, n);
    for(int i=0;i<m;i++){
        int op;
        cin >> op;
        if(op==1){
        int x,y,z;
        cin >> x >> y >> z;
        update_path(x,y,z);
    }
    else if(op==2){
        int x,y;
        cin >> x >> y;
        cout << query_path(x,y) << endl;
    }
    else if(op==3){
        int x,z;
        cin >> x >> z;
        update_tree(x,z);
    }
    else if(op==4){
        int x;
        cin >> x;
        cout << query_tree(x) << endl;
    }
}
    return 0;
}