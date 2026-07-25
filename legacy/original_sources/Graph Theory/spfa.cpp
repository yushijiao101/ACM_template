#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100010;
const int INF = 0x3f3f3f3f; // 用一个足够大的数代表无穷大

int n, m, s;
vector<vector<pair<int, int>>> adj(Maxn);
vector<int> dis(Maxn, INF); 
vector<bool> in_queue(Maxn, false); // 标记节点是否【正在】队列中
vector<int> cnt(Maxn, 0);          // 记录每个节点入队的次数，用于判负环

void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w}); 
}

// SPFA 算法
bool spfa() {
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false; // 出队后重置标记

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;

            if (dis[v] > dis[u] + w) { // 松弛操作
                dis[v] = dis[u] + w;
                
                // 如果 dis[v] 被更新了，且 v 不在队列中，就让它入队
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                    cnt[v]++; // 入队次数自增
                    
                    // 关键：如果一个点入队超过 n 次，说明存在负环
                    if (cnt[v] >= n) return false; 
                }
            }
        }
    }
    return true; // 没有负环
}

int main() {
    ios::sync_with_stdio(false); // 加速读入
    cin.tie(0);

    if (!(cin >> n >> m >> s)) return 0;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    if (!spfa()) {
        cout << "NO SOLUTION" << endl; // 差分约束中代表不等式组冲突
    } else {
        for (int i = 1; i <= n; i++) {
            if (dis[i] == INF) cout << "INF ";
            else cout << dis[i] << " ";
        }
        cout << endl;
    }

    return 0;
}