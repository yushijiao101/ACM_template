#include <bits/stdc++.h>
using namespace std;
typedef int long long;

const int MAXN = 200005;

struct Node {
    int sum;  // 存储区间和
    int add;  // 存储加法懒标记
    // 如果有区间修改，可以再加个 int setVal 和 bool hasSet
} tree[MAXN << 2]; // 直接开4倍数组，比 vector 快且简洁

int a[MAXN]; // 原数组

// 辅助函数：计算子节点编号
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }

// 向上更新：用儿子更新父亲
void push_up(int p) {
    tree[p].sum = tree[ls(p)].sum + tree[rs(p)].sum;
}

// 向下更新：把懒标记传给儿子
void push_down(int p, int l, int r) {
    if (tree[p].add != 0) {
        int mid = (l + r) >> 1;
        
        // 处理左儿子
        tree[ls(p)].add += tree[p].add;
        tree[ls(p)].sum += tree[p].add * (mid - l + 1);
        
        // 处理右儿子
        tree[rs(p)].add += tree[p].add;
        tree[rs(p)].sum += tree[p].add * (r - mid);
        
        // 清空父节点标记
        tree[p].add = 0;
    }
}

// 建树
void build(int p, int l, int r) {
    tree[p].add = 0;
    if (l == r) {
        tree[p].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}

// 区间加法：[ql, qr] 是目标，[l, r] 是当前
void update(int p, int l, int r, int ql, int qr, int val) {
    // 1. 目标区间完全包含当前区间
    if (ql <= l && r <= qr) {
        tree[p].sum += val * (r - l + 1);
        tree[p].add += val;
        return;
    }
    // 2. 否则，先下放标记，再递归
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ls(p), l, mid, ql, qr, val);
    if (qr > mid)  update(rs(p), mid + 1, r, ql, qr, val);
    push_up(p);
}

// 区间查询
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p].sum;
    
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(ls(p), l, mid, ql, qr);
    if (qr > mid)  res += query(rs(p), mid + 1, r, ql, qr);
    return res;
}
signed main() {
    // 1. 加速输入输出（这一步在竞赛中非常重要）
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 2. 读取原始数据（假设数组 a 已经在全局定义或足够大的地方）
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 3. 建树：根节点编号为 1，管辖范围 [0, n-1]
    build(1, 0, n - 1);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            // 区间加法：[x, y] 每个数加 k
            int x, y;
            int k;
            cin >> x >> y >> k;
            // 题目通常给 1-indexed，我们要转成 0-indexed
            update(1, 0, n - 1, x - 1, y - 1, k);
        } 
        else if (op == 2) {
            // 区间查询：求 [x, y] 的和
            int x, y;
            cin >> x >> y;
            cout << query(1, 0, n - 1, x - 1, y - 1) << "\n";
        }
    }

    return 0;
}