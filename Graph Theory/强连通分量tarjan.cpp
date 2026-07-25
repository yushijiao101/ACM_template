#include <bits/stdc++.h>
using namespace std;
const int N=5*1e5;
    int dfn[N], low[N], idx=0;
    int stk[N], instk[N], ptr = 0;
    int scc[N], siz[N], scc_cnt=0;
        vector<vector<int>> G(N);
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
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    tarjan(1);
    return 0;
}