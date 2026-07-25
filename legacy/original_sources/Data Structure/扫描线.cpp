#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN = 200005;

struct line {
    ll x1,x2,y;
    ll tag; // 入边+1 出边-1
    bool operator < (const line &other) const {
        return y < other.y; // 按照 y 坐标排序
    }
} L[MAXN]; // 直接开4倍数组，比 vector 快且简洁

struct tree
{
    ll l,r;
    ll cnt,len; // cnt 代表当前区间被覆盖了几层，len 代表当前区间被覆盖的长度
} tree[MAXN << 3];      

ll X[MAXN]; // X 坐标离散化数组

// 辅助函数：计算子节点编号
inline ll ls(ll p) { return p << 1; }
inline ll rs(ll p) { return p << 1 | 1; }

// 向上更新：用儿子更新父亲
void push_up(ll u) {
    ll l=tree[u].l,r=tree[u].r;//r->X[r+1]
    if(tree[u].cnt) tree[u].len=X[r+1]-X[l]; // 如果当前区间被覆盖了至少一层，那么它的长度就是 X[r+1]-X[l]
    else tree[u].len=tree[ls(u)].len+tree[rs(u)].len; // 否则，长度等于左右儿子长度之和
}

void modify(ll u,ll l,ll r,ll tag) {
    if(tree[u].l>=l&&tree[u].r<=r) {
        tree[u].cnt+=tag;
        push_up(u);
        return;
    }
    ll mid=(tree[u].l+tree[u].r)>>1;
    if(l<=mid) modify(ls(u),l,r,tag);
    if(r>mid) modify(rs(u),l,r,tag);
    push_up(u);
}

// 建树
void build(ll p, ll l, ll r) {
    tree[p].l = l;
    tree[p].r = r;
    tree[p].cnt = 0;
    tree[p].len = 0;
    if(l==r) return; // 叶节点不需要继续建树了
    ll mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}


int main() {
    // 1. 加速输入输出（这一步在竞赛中非常重要）
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    if (!(cin >> n)) return 0;

    // 2. 读取原始数据（假设数组 a 已经在全局定义或足够大的地方）
    for (ll i = 0; i < n; i++) {
        ll x1,x2,y1,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        L[i]={x1,x2,y1,1}; // 入边
        L[i+n]={x1,x2,y2,-1}; // 出边
        X[i]=x1;
        X[i+n]=x2;
    }
    n=n*2; // 现在 n 是线段数量的两倍了
    //排序
    sort(L,L+n);
    sort(X,X+n);
    ll s=unique(X,X+n)-X; // 离散化后坐标数量
    // 3. 建树：根节点编号为 1，管辖范围 [0, n-1]
    build(1, 0, s - 2);//s-2 是因为线段树是基于区间的，而离散化后坐标是点的，所以区间数量比点数量少1

    ll ans=0;
    for(ll i=0;i<n;i++){
        ll l=lower_bound(X,X+s,L[i].x1)-X; // 离散化坐标
        ll r=lower_bound(X,X+s,L[i].x2)-X; 
        modify(1,l,r-1,L[i].tag); //传参的时候是r-1，因为线段树是基于区间的，而离散化后坐标是点的，所以区间数量比点数量少1
        if(i<n-1) ans+=tree[1].len*(L[i+1].y-L[i].y); // 计算面积增量
    }
    cout << ans << endl;
    return 0;
}