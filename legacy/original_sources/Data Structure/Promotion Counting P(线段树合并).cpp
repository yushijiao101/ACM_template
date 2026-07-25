#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define ls(x) tr[x].ch[0]
#define rs(x) tr[x].ch[1]
int n,m,a[N];
vector<int> v;
struct node{
    int ch[2];
    int val;
}tr[N*22];
int root[N],idx;
vector<vector<int>> g(N);
int fa[N];
void insert(int &y,int l,int r,int v){
    y=++idx;//y为当前节点编号
    tr[y].val++;
    if(l==r) return;
    int mid=(l+r)>>1; //双指针同步搜索
    if(v<=mid) insert(ls(y),l,mid,v);
    else insert(rs(y),mid+1,r,v);
}
void merge(int &x,int y){
    if(!(x&&y)) x|=y;    //y合并到x上 当然写成x+=y也行  //让x=max(x,y);
    else{    //如果x，y都有东西
    tr[x].val+=tr[y].val;
    merge(ls(x),ls(y));
    merge(rs(x),rs(y));
    }
}
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tr[p].val;
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(ls(p), l, mid, ql, qr);
    if (qr > mid)  res += query(rs(p), mid + 1, r, ql, qr);
    return res;
}
int ans[N];
int getid(int x){
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
void dfs(int r){
    for(auto it:g[r]){
        if(fa[r]==it) continue;
        else dfs(it);
        merge(root[r],root[it]);
    }
    ans[r]=query(root[r],1,n,getid(a[r])+1,n);    
}
void add(int x,int y){
    g[x].push_back(y);
    g[y].push_back(x);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    for(int i=2;i<=n;i++){
        int x;
        cin >> x;
        add(x,i);
        fa[i]=x;
    }
    for(int i=1;i<=n;i++) insert(root[i],1,n,getid(a[i]));//每个点动态开线段树
    dfs(1);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
}