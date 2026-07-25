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
vector<vector<int>> point(101,vector<int>(26,0));

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for(int ca=1;ca<=t;ca++){
        int n,k;
        cin >> n >>k;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                cin >> point[i][j];
            }
        }
        Flow solve(2*n+2);

    // 建立源点 0 到左侧二分图的边
    for (int i = 1; i <= n; i++) {
        solve.add(0, i, 1);
    }
    // 建立右侧二分图到汇点 2*n+1 的边
    for (int i = n + 1; i <= 2*n; i++) {
        solve.add(i, 2*n + 1, 1);
    }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j) continue;
                int flag=0;
                for(int tt=1;tt<=k;tt++) if(point[i][tt]>=point[j][tt]) flag=1;
                if(!flag) solve.add(i,j+n,1);
            }    
        }
        cout<<"Case #"<<ca<<": "<<n-solve.work(0,2*n+1)<<endl;
    }
    return 0;
}