#include <bits/stdc++.h>
using namespace std;
const int N=5*1e5;
    int dfn[N], low[N], idx=0;
    int stk[N], instk[N], ptr = 0;
    int scc[N], siz[N], scc_cnt=0;
    int val[N], new_val[N], dp[N];
        vector<vector<int>> G;
void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++ptr]=u;
    instk[u] = true;

    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(instk[v]) low[u] = min(low[u], dfn[v]);
    }

    if(dfn[u]==low[u]){
        int y;
        scc_cnt++;
        do{
            y=stk[ptr--];
            instk[y]=false;
            scc[y]=scc_cnt;
            siz[scc_cnt]++;
        }while(y!=u);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    G.resize(n+1);
    for(int i=0;i<n;i++){
        cin>>val[i+1];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    //建立缩点后的新图
    vector<vector<int>> newG(scc_cnt+1);
    vector<int> in_d(scc_cnt+1);
    for(int i=1;i<=n;i++){
        new_val[scc[i]]+=val[i];
        for(int j:G[i]){
            if(scc[i]!=scc[j]){
                newG[scc[j]].push_back(scc[i]);
                in_d[scc[i]]++;
            }
        }
    }
    memset(dp,0,sizeof(dp));
    queue<int> q;
    for(int i=1;i<=scc_cnt;i++){
        if(in_d[i]==0) {q.push(i);dp[i]=new_val[i];}
    }
    while(!q.empty()){
        int t=q.front();
        for(auto it:newG[t]){
            in_d[it]--;
            if(in_d[it]==0) q.push(it);
            dp[it]=max(dp[t]+new_val[it],dp[it]);
        }
        q.pop();

    }
    int maxx=0;
    for(int i=1;i<=scc_cnt;i++){
        maxx=max(maxx,dp[i]);
    }
    cout<<maxx<<endl;
    return 0;
}