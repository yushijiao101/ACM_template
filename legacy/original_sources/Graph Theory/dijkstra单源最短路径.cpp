#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100010;
int n, m, s;
vector<vector<pair<int, int>>> adj(Maxn);
vector<int> dis(Maxn, INT_MAX); 
vector<bool> vis(Maxn, 0); 

void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w}); 
}

// Dijkstra 算法
void dijkstra() {
    dis[s] = 0; // 起点到自身的距离为 0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s}); // 起点入队

    while (!q.empty()) {
        int node = q.top().second; // 当前节点
        int d = q.top().first; // 当前节点的距离
        q.pop();

        if (vis[node]) continue; // 如果已经访问过，跳过
        vis[node] = 1; // 标记为已访问

        // 遍历所有从当前节点出发的边
        for (auto it : adj[node]) {
            int a = it.first; // 目标节点
            int b = it.second; // 边的权重
            if (dis[a] > dis[node] + b) { // 松弛操作
                dis[a] = dis[node] + b;
                q.push({dis[a], a}); // 更新距离并加入队列
            }
        }
    }
}

int main() {
    cin >> n >> m >> s; // 输入节点数、边数和起点
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w; // 输入边的信息
        add_edge(u, v, w); // 添加边
    }

    dijkstra(); // 运行 Dijkstra 算法

    // 输出从起点到每个节点的最短距离
    for (int i = 1; i <= n; i++) {
            cout << dis[i] << " ";
    }
    return 0;
}