#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define lc(x) tr[x].ch[0]
#define rc(x) tr[x].ch[1]
int n,m,a[N];
const int L = 20;       // 2^20 > 1e6，足够覆盖常见数据
vector<vector<int>> g(N);      // 邻接表
int fa[N][L];        // fa[u][k]表示u的2^k级祖先
int depth[N];           // 节点深度

void bfs(int s) {
    queue<int> q;
    q.push(s);
    memset(fa, -1, sizeof(fa));  
    memset(depth, -1, sizeof(depth));  
    depth[s] = 0;          
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (depth[v] == -1) {     
                depth[v] = depth[u] + 1;
                fa[v][0] = u;        
                q.push(v);
                for (int k = 1; k < L; ++k) {
                    if (fa[v][k-1] != -1) fa[v][k] = fa[fa[v][k-1]][k-1];
                    else break; 
                }
            }
        }
    }
}
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int k = L-1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            u = fa[u][k];
        }
    }
    if (u == v) return u;
    for (int k = L-1; k >= 0; --k) {
        if (fa[u][k] != fa[v][k]) { 
            u = fa[u][k];
            v = fa[v][k];
        }
    }
    return fa[u][0];  
}
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
int query(int x,int y, int la, int fla, int l,int r,int v){
    if(l==r) return l;
    int mid=(l+r)>>1;
    int cnt=tr[lc(y)].s+tr[lc(x)].s-tr[lc(la)].s-tr[lc(fla)].s;//统计左子树中有多少个数 
    if(cnt>=v) return query(lc(x),lc(y),lc(la),lc(fla),l,mid,v);
    else return query(rc(x),rc(y),rc(la),rc(fla),mid+1,r,v-cnt);
}
int getid(int x){
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
    int vn;
void dfs(int s){
    int f=fa[s][0];
    insert(root[f],root[s],1,vn,getid(a[s]));
    for(auto t:g[s]) if(t!=f) dfs(t);
    return;
}
void add(int x,int y){
g[x].push_back(y);
g[y].push_back(x);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        v.push_back(a[i]);
    }
    for(int i=1;i<n;i++){
        int a,b;
        cin >> a >> b;
        add(a,b);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vn=v.size();
    bfs(1);
    insert(root[0],root[1],1,vn,getid(a[1]));
    dfs(1);
    // for(int i=1;i<=n;i++) insert(root[i-1],root[i],1,vn,getid(a[i]));
    int last=0;
    for(int i=1;i<=m;i++){
        int aa,bb,k;
        cin>>aa>>bb>>k;
        aa=aa^last;
        int la=lca(aa,bb);
        int ula=fa[la][0];
        last=v[query(root[aa],root[bb],root[la],root[ula],1,vn,k)-1];
        cout<<last<<endl;//查询
    } 
}