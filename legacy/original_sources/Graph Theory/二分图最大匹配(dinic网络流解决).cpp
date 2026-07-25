#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;

struct Flow {
    const int n; // 节点的总个数
    struct Edge {
        int to;
        int w;
    };
    vector<Edge> ver;
    vector<vector<int>> h;
    vector<int> cur, d;

    // 正确的构造函数：初始化实例时必须给成员变量分配空间
    Flow(int _n) : n(_n), h(_n), cur(_n), d(_n) {}

    void add(int u, int v, int c) {
        h[u].push_back(ver.size());
        ver.emplace_back(Edge{v, c});
        h[v].push_back(ver.size());
        ver.emplace_back(Edge{u, 0}); // 反向边，初始容量为 0
    }

    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto it : h[x]) {
                auto [y, w] = ver[it];
                if (w && d[y] == -1) {
                    d[y] = d[x] + 1;
                    if (y == t) return true;
                    q.push(y);
                }
            }
        }
        return false;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        auto r = f;
        for (int &i = cur[u]; i < h[u].size(); i++) {
            auto j = h[u][i];
            auto &[v, c] = ver[j];
            auto &[from, rc] = ver[j ^ 1];
            if (c && d[v] == d[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                c -= a;
                rc += a;
                r -= a;
                if (!r) return f;
            }
        }
        return f - r;
    }

    int work(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0); // 当前弧优化重置
            ans += dfs(s, t, inf);
        }
        return ans;
    }
};

signed main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, e;
    if (!(cin >> n >> m >> e)) return 0;

    // 实例化 Flow 结构体，总节点数传递给构造函数
    Flow solve(n + m + 2);

    // 建立源点 0 到左侧二分图的边
    for (int i = 1; i <= n; i++) {
        solve.add(0, i, 1);
    }
    // 建立右侧二分图到汇点 n+m+1 的边
    for (int i = n + 1; i <= n + m; i++) {
        solve.add(i, n + m + 1, 1);
    }
    // 读入二分图的边
    for (int i = 1; i <= e; i++) {
        int u, v;
        cin >> u >> v;
        solve.add(u, n + v, 1);
    }

    cout << solve.work(0, n + m + 1) << "\n";

    return 0;
}