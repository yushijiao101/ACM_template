#include <bits/stdc++.h>
using namespace std;
const int N = 2*1e5+5;
vector<int> cnt(N);//我们记录第k次操作后栈中还剩多少元素
class DSU {
private:
    vector<int> parent;
    vector<int> rank; // 用于按秩合并，优化树的高度
    stack<vector<int>> stk;

  public:
	DSU(int size) : parent(size), rank(size, 1) {
		for (int i = 1; i < size; i++) { parent[i] = i; }
	}

    // 查找操作：包含路径压缩 (Path Compression)
    int find(int x) {
        while (parent[x] != x) {
            x=parent[x];
        }
        return x;
    }

    // 合并操作：包含按秩合并 (Union by Rank)
    void unite(int x, int y) {
        int flag=0;
        int rx = find(x);
        int ry = find(y);
        
        if (rx != ry) {
            // 将高度小的树合并到高度大的树下
            if (rank[rx] > rank[ry]) {
                swap(rx,ry);
            } 
            //让x作为秩小的 指向y
            parent[rx] = ry;
            if (rank[rx] == rank[ry])  {flag=1;rank[ry]++;}
                       stk.push({rx,ry,flag});
            }
        }
    void undo(){
        if(stk.empty()) return;
            int rx = stk.top()[0];
			int ry = stk.top()[1];
			int flag = stk.top()[2]; 
			stk.pop();
            parent[rx]=rx;
            parent[ry]=ry;
            if(flag==1) ry--;
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

    int n, q;
    cin >> n >> q;
    DSU dsu(n+1);

    for (int i = 0; i < q; ++i) {
        int op;
        cin >> op;

        if (op == 1) {
            int x,y;
            cin >> x >> y;
            dsu.unite(x, y);
        } 
        else if (op == 2) {
            dsu.undo();
        }
        else{
            int x,y;
            cin >> x >> y;
            if(dsu.isConnected(x,y)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
}


int main() {
    solve();
    return 0;
}