#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int M = 300005;

struct Edge {
    int a, b, val;
} edge[M];

int n, m, q;
int w[N];
int parent[N]; 
vector<int> g[N]; // 必须建图才能进行 DFS
int fa[N], dep[N], sz[N], son[N], top[N];
int node_cnt; // 记录重构树节点总数

int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y, int val) {
    int ra = find(x);
    int rb = find(y);
    if (ra != rb) {
        node_cnt++; // 新建节点
        parent[ra] = node_cnt;
        parent[rb] = node_cnt;
        parent[node_cnt] = node_cnt;
        
        w[node_cnt] = val;
        g[node_cnt].push_back(ra);
        g[node_cnt].push_back(rb);
        fa[ra] = node_cnt;
        fa[rb] = node_cnt;
    }
}

void dfs1(int u, int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    son[u] = 0; // 初始化重儿子
    for (auto v : g[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    if (!(cin >> n >> m)) return 0;

    node_cnt = n;
    for (int i = 1; i <= 2 * n; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        cin >> edge[i].a >> edge[i].b >> edge[i].val;
    }
    sort(edge, edge + m, [](const Edge &a, const Edge &b) {
        return a.val < b.val;
    });

    for (int i = 0; i < m; i++) {
        unite(edge[i].a, edge[i].b, edge[i].val);
    }

    for (int i = node_cnt; i >= 1; i--) {
        if (!dep[i]) {
            dfs1(find(i), 0);
            dfs2(find(i), find(i));
        }
    }

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (find(a) != find(b)) cout << "impossible" << endl;
        else cout << w[lca(a, b)] << endl;
    }
    return 0;
}