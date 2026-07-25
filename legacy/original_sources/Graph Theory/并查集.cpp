#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank; // 用于按秩合并，优化树的高度


  public:
	DSU(int size) : parent(size), rank(size, 1) {
		for (int i = 0; i < size; i++) { parent[i] = i; }
	}

    // 查找操作：包含路径压缩 (Path Compression)
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]); // 递归并压缩
    }

    // 合并操作：包含按秩合并 (Union by Rank)
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // 将高度小的树合并到高度大的树下
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // 判断是否属于同一集合
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    // 优化标准输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return;

    DSU dsu(n);

    for (int i = 0; i < m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            dsu.unite(x, y);
        } else if (op == 2) {
            if (dsu.isConnected(x, y)) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        }
    }
}

int main() {
    solve();
    return 0;
}