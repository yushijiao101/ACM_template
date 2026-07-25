#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N = 200005;
#define mid ((l+r)>>1)
struct Node {
    int x;  // 区间x和
    int x2;
    int y;  // 区间y和
    int y2;
} tr[N << 2]; // 直接开4倍数组，比 vector 快且简洁

vector<pii> a(N);
// 辅助函数：计算子节点编号
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }

// 向上更新：用儿子更新父亲
void push_up(int p) {
    tr[p].x = tr[ls(p)].x + tr[rs(p)].x;
    tr[p].y = tr[ls(p)].y + tr[rs(p)].y;
    tr[p].x2 = tr[ls(p)].x2 + tr[rs(p)].x2;
    tr[p].y2 = tr[ls(p)].y2 + tr[rs(p)].y2;
}


// 建树
void build(int p, int l, int r) {
    if (l == r) {
        tr[p].x = a[l].first;
        tr[p].x2 =a[l].first*a[l].first;
        tr[p].y = a[l].second;
        tr[p].y2 = a[l].second*a[l].second;
        return;
    }
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}

// 区间加法：[ql, qr] 是目标，[l, r] 是当前
void update1(int p, int l, int r, int t, pii pa) {
    if (l == t && r == t) {
        tr[p].x += pa.first;
        tr[p].x2=tr[p].x*tr[p].x;
        tr[p].y += pa.second;
        tr[p].y2=tr[p].y*tr[p].y;
        return;
    }
    if (t <= mid) update1(ls(p), l, mid, t, pa);
    if (t > mid)  update1(rs(p), mid + 1, r, t, pa);
    push_up(p);
}

void update2(int p, int l, int r, int t, int ratio) {
    if (l == t && r == t) {
        tr[p].x *=ratio;
        tr[p].x2=tr[p].x*tr[p].x;
        tr[p].y *=ratio;
        tr[p].y2=tr[p].y*tr[p].y;
        return;
    }
    if (t <= mid) update2(ls(p), l, mid, t, ratio);
    if (t > mid)  update2(rs(p), mid + 1, r, t, ratio);
    push_up(p);
}
// 区间查询
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return (tr[p].x*tr[p].x-tr[p].x2+tr[p].y*tr[p].y-tr[p].y2)/2;
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
    cin >> n >> m;

    // 2. 读取原始数据（假设数组 a 已经在全局定义或足够大的地方）
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    // 3. 建树：根节点编号为 1，管辖范围 [0, n-1]
    build(1, 0, n - 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, x, y;
            cin >> i >> x >> y ;
            update1 (1, 0, n - 1, i, {x,y});
        } 
        else if (op == 2) {
            int i, x, y;
            cin >> i >> x >> y ;
            update1 (1, 0, n - 1, i, {-x,-y});
        }
        else if (op == 3) {
            int i, t;
            cin >> i >> t;
            update2 (1, 0, n - 1, i, t);
        }
        else if (op == 4) {
            int x, y;
            cin  >> x >> y ;
            cout<<query(1,0,n-1,x,y);
        }
    }

    return 0;
}