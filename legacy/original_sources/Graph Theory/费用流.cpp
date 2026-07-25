#include <bits/stdc++.h>
using namespace std;

template<typename T> struct MCMF {
    const int n;
    const T inf = numeric_limits<T>::max();
    
    struct Edge {
        int to;
        T cap;  // 容量 (原代码的 w)
        T cost; // 费用 (新增)
        Edge(int to, T cap, T cost) : to(to), cap(cap), cost(cost) {}
    };

    vector<Edge> ver;
    vector<vector<int>> h;
    vector<int> cur;
    vector<T> dis;      // 存储起点到各点的最小费用
    vector<bool> vis;   // SPFA 和 DFS 中防止环的访问标记

    MCMF(int n) : n(n + 1), h(n + 1), dis(n + 1), vis(n + 1) {}

    // 加边：增加 cost 参数
    void add(int u, int v, T cap, T cost) {
        h[u].push_back(ver.size());
        ver.emplace_back(v, cap, cost);
        h[v].push_back(ver.size());
        ver.emplace_back(u, 0, -cost); // 反向边容量0，费用为负
    }

    // SPFA: 寻找单位费用最小的路径 (代替原来的 BFS)
    bool spfa(int s, int t) {
        dis.assign(n, inf);
        vis.assign(n, false); // 这里 vis 用于记录是否在队列中
        
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (auto i : h[u]) {
                auto [v, cap, cost] = ver[i];
                // 如果有残量 且 走这条边能让费用更小
                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[t] != inf; // 如果能走到汇点，说明还有路
    }

    // DFS: 多路增广推流
    T dfs(int u, int t, T flow, T& total_cost) {
        if (u == t) return flow;
        
        vis[u] = true; // 标记当前路径已访问，防止0费用环死循环
        T used = 0;

        for (int &i = cur[u]; i < h[u].size(); i++) {
            int idx = h[u][i];
            auto &[v, cap, cost] = ver[idx];
            
            // 核心判断：只走就在最短路上的边 (dis[v] == dis[u] + cost)
            if (cap > 0 && !vis[v] && dis[v] == dis[u] + cost) {
                T ret = dfs(v, t, min(flow - used, cap), total_cost);
                
                if (ret > 0) {
                    cap -= ret;
                    ver[idx ^ 1].cap += ret;
                    used += ret;
                    total_cost += ret * cost; // 累计费用
                    
                    if (used == flow) break; 
                }
            }
        }
        
        vis[u] = false; // 回溯
        if (used == 0) dis[u] = -inf; // 剪枝：这个点走不通，暂时移出最短路图
        return used;
    }

    // 返回 pair: {最大流, 最小费用}
    pair<T, T> work(int s, int t) {
        T max_flow = 0;
        T min_cost = 0;
        
        while (spfa(s, t)) {
            cur.assign(n, 0);
            dfs(s, t, inf, min_cost); 
        }
        
        max_flow = 0; 
        min_cost = 0;
        while(spfa(s, t)) {
            cur.assign(n, 0);
            vis.assign(n, false); // DFS 前清空 vis
            max_flow += dfs(s, t, inf, min_cost);
        }

        return {max_flow, min_cost};
    }
};

int main(){
    int m, n;

    cin >> m >> n;
    
    using f = MCMF<long long>;
    f solve(n + 2);
    
    while(1){
        int u, v;
        cin >> u >> v; 
        if(u == -1 && v == -1) break;
        // 假设中间的边：容量 1，费用 1 (举例)
        // add(u, v, cap, cost)
        solve.add(u, v, 1, 1); 
    }
    
    // 源点到左侧：容量 1，费用 0
    for(int i = 1; i <= m; i++) solve.add(0, i, 1, 0);
    
    // 右侧到汇点：容量 1，费用 0
    for(int i = m + 1; i <= n; i++) solve.add(i, n + 1, 1, 0);
    
    auto [flow, cost] = solve.work(0, n + 1);
    cout << "Max Flow: " << flow << endl;
    cout << "Min Cost: " << cost << endl;
    
    // 输出匹配方案
    for(int i = 1; i <= m; i++){
        for(auto idx : solve.h[i]){
            auto e = solve.ver[idx];
            // 判断正向边，且满流 (cap == 0 说明流过去了)
            // 且这不是连向源点的反向边 (e.to != 0)
            if(e.to != 0 && e.cap == 0 && e.cost > 0) { // e.cost > 0 过滤掉反向边
               // 注意：由于 ver 里的 cost 是原始 cost，
               // 正向边加入时是正的，反向边是负的。
               // e.cap == 0 代表这条容量为 1 的边被用掉了
               cout << i << " " << e.to << endl;
            }
        }
    }
}