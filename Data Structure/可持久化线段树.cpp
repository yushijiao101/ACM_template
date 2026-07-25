#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define lc(x) tr[x].ch[0]
#define rc(x) tr[x].ch[1]
int n,m,a[N];
vector<int> v;
struct node{
    int ch[2];
    int s;
}tr[N*22];
int root[N],idx;
void build(int &x,int l,int r){
    x=++idx;//x为当前节点编号 
    if(l==r) return;
    int mid=(l+r)>>1;
    build(lc(x),l,mid);
    build(rc(x),mid+1,r);
}   
void insert(int x,int &y,int l,int r,int v){
    y=++idx;//y为当前节点编号
    tr[y]=tr[x];
    tr[y].s++;
    if(l==r) return;
    int mid=(l+r)>>1; //双指针同步搜索
    if(v<=mid) insert(lc(x),lc(y),l,mid,v);
    else insert(rc(x),rc(y),mid+1,r,v);
}
int query(int x,int y, int l,int r,int v){
    if(l==r) return l;
    int mid=(l+r)>>1;
    int cnt=tr[lc(y)].s-tr[lc(x)].s;//统计左子树中有多少个数 
    if(cnt>=v) return query(lc(x),lc(y),l,mid,v);
    else return query(rc(x),rc(y),mid+1,r,v-cnt);
}
int getid(int x){
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int vn=v.size();
    for(int i=1;i<=n;i++) insert(root[i-1],root[i],1,vn,getid(a[i]));
    for(int i=1;i<=m;i++){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<v[query(root[l-1],root[r],1,vn,k)-1]<<endl;//查询第k小的数
    } 
}