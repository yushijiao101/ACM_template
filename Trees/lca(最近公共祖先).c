#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;  // 根据题目最大节点数调整
const int L = 20;       // 2^20 > 1e6，足够覆盖常见数据
vector<vector<int>> g(N);      // 邻接表
int fa[N][L];        // fa[u][k]表示u的2^k级祖先
int depth[N];           // 节点深度

void bfs(int root) {
    queue<int> q;
    q.push(root);
    memset(depth, -1, sizeof(depth));  // 初始化祖先为-1
    memset(fa, -1, sizeof(fa));  // 初始化祖先为-1
    depth[root] = 0;             // 根节点深度为0

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // 预处理直接父节点 (2^0级祖先)
        for (int v : g[u]) {
            if (depth[v] == -1) {      // 未访问过
                depth[v] = depth[u] + 1;
                fa[v][0] = u;          // 直接父节点
                q.push(v);
                
                // 预处理2^k级祖先 (动态规划)
                for (int k = 1; k < L; ++k) {
                    if (fa[v][k-1] != -1) fa[v][k] = fa[fa[v][k-1]][k-1];  // 如果2^(k-1)级祖先存在
                    else break;  // 祖先不存在时停止
                }
            }
        }
    }
}

// 查询LCA核心逻辑
int lca(int u, int v) {
    // 保证u是较深的节点
    if (depth[u] < depth[v]) swap(u, v);
    
    // 先跳到同一深度
    for (int k = L-1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            u = fa[u][k];
        }
    }
    
    if (u == v) return u;  // 刚好是同一个节点
    
    // 一起向上跳
    for (int k = L-1; k >= 0; --k) {
        if (fa[u][k] != fa[v][k]) {  // 祖先不同才跳转
            u = fa[u][k];
            v = fa[v][k];
        }
    }
    return fa[u][0];  // 最终父节点即LCA
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, s;
    cin >> n >> m >> s;//s为根节点 一般为0
    g.resize(n+1);
    memset(depth, -1, sizeof(depth));
    
    // 建树
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // 预处理
    bfs(s);
    //bfs(0); //如果根节点为0则使用此行代码
    
    // 处理查询
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
    return 0;
}
//我们可以通过lca很简单的求出树两点间的距离
//d(u, v) = depth[u] + depth[v] - 2 × depth[lca(u, v)]