#include <bits/stdc++.h>
using namespace std;

struct Connect {
    pair<int, int> a;
    int value;
};

struct Compare {
    bool operator()(Connect a, Connect b) const {
        return a.value > b.value;  
    }
};

vector<Connect> edges;  // 存储所有边
priority_queue<Connect, vector<Connect>, Compare> pq;  // 小顶堆
vector<int> fa;  // 并查集

void add(int u, int v, int w) {
    Connect edge;
    edge.a.first = u;
    edge.a.second = v;
    edge.value = w;
    edges.push_back(edge);
}

int find(int a) {
    if (fa[a] == a) return a;
    return fa[a] = find(fa[a]);  // 路径压缩
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    // 初始化并查集
    fa.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    // 输入边
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }

    // 将所有边加入优先队列
    for (auto it : edges) {
        pq.push(it);
    }
int max_value=0;
    while (!pq.empty()) {
        Connect edge = pq.top();
        pq.pop();
        int u = edge.a.first, v = edge.a.second;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            fa[fu] = fv;  // 合并集合
            max_value=max(max_value,edge.value);
        }
        if(find(s)==find(t)) break;
    }
    cout << max_value << endl;
    return 0;
}