#include <bits/stdc++.h>
using namespace std;
#define int long long
class DSU {
private:
    vector<int> parent;
    vector<int> rank; // 用于按秩合并，优化树的高度


  public:
	DSU(int size) : parent(size), rank(size, 1) {
		for (int i = 1; i < size; i++) { parent[i] = i; }
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

    int n, k;
    cin >> n >> k;
    int ans=0;
    DSU dsu(3*n+1); 
    //我们分出三个域x x+n x+2*n 作为x同类 被x捕食的同类 捕食x的同类
    for (int i = 0; i < k; ++i) {
        int op,x,y;
        cin >> op >> x >> y;
        if(x>n||y>n) {ans++;continue;}
        if(op==1){
        //先判断是否矛盾 如果x和y已经不是同类 也就是x和y+n 或者x和y+2*n之间联通 则与前面冲突
            if(dsu.find(x)==dsu.find(y+n)||dsu.find(x)==dsu.find(y+2*n)) {ans++;continue;}
            dsu.unite(x,y);
            dsu.unite(x+n,y+n);
            dsu.unite(x+2*n,y+2*n);
        }
        else if(op==2){
        if(x==y) {ans++;continue;}
        //先判断是否矛盾 x和y 或者x和y+n之间联通 则与前面冲突
        if(dsu.find(x)==dsu.find(y+n)||dsu.find(x)==dsu.find(y)) {ans++;continue;}
            dsu.unite(x,y+2*n);
            dsu.unite(x+n,y);
            dsu.unite(x+2*n,y+n);
        }
    }
    cout<<ans;
}

signed main() {
    solve();
    return 0;
}