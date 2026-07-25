#include <bits/stdc++.h>
using namespace std;
const int N=5*1e5;
int dfn[N], low[N], idx=0;
vector<bool> cut(N,0);
int root;//记录开始dfs的根节点
        vector<vector<int>> G(N);
void tarjan(int u,int root) {
    // 1 压栈 记录编号
    dfn[u] = low[u] = ++idx;
    int child=0;
    // 2 遍历邻边 tarjan深搜 并且更新回溯值
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v,root);
            low[u] = min(low[u], low[v]);//自己或子节点能访问到的最早的时间戳
            if(low[v]>=dfn[u]) {
                child++;
                }
        }
    else{    
        //  处理反祖边
        low[u]=min(low[u],dfn[v]);
}
if(u!=root&&child) cut[u]=true;
else if(u==root&&child>=2) cut[u]=true;
    }
}
    int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i,i);
    }
        vector<int> ans;
        int res=0;
        for(int i=1;i<=n;i++) if(cut[i]) ans.push_back(i);
        cout<<ans.size()<<endl;
        for(auto it:ans) cout<<it<<" ";
        return 0;
    }