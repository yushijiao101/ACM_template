#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5; // 增加范围
vector<pair<int, int>> G[MAXN]; // node, edge_id
int degree[MAXN];
bool used_edge[MAXN]; // 标记边是否访问过
int del[MAXN]; // 当前处理到第几条边
stack<int> stk;

void dfs(int u) {
    for (int &i = del[u]; i < G[u].size(); ) {// 引用传递并自增，实现真正的跳过
        pair<int, int> edge = G[u][i++]; 
        if (used_edge[edge.second]) continue;
        used_edge[edge.second] = true;
        dfs(edge.first);
    }
    stk.push(u);
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({v, i});
        G[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    // 排序以保证字典序（如果题目有要求）
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }

    int start_node = 1;
    int odd_count = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            odd_count++;
        }
    }
    if(odd_count==0) ;
    else if (odd_count!=2||degree[1]%2==0) {cout<<-1;return 0;}
    dfs(start_node);

    if (stk.size() != m + 1) { // 检查连通性（边是否全部走过）
        cout << -1 << endl;
    } else {
        while (!stk.empty()) {
            cout << stk.top() << (stk.size() == 1 ? "" : " ");
            stk.pop();
        }
    }

    return 0;
}
