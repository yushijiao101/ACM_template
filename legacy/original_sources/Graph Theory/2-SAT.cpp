#include <bits/stdc++.h>
using namespace std;
const int N=2*1e6+5;
    int dfn[N], low[N], idx=0;
    int stk[N], instk[N], ptr = 0;
    int scc[N], siz[N], scc_cnt=0;
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
    G.resize(2*n+1);
    for(int k=0;k<m;k++){
        int i,a,j,b;
        cin >> i >> a >> j >> b;
        G[i+!a*n].push_back(j+b*n);
        G[j+!b*n].push_back(i+a*n);
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]) tarjan(i);
    }
    //建立缩点后的新图
    vector<vector<int>> newG(scc_cnt+1);
    vector<int> in_d(scc_cnt+1);
    int flag=0;
    for(int i=1;i<=n;i++) if(scc[i]==scc[i+n]) {cout<<"IMPOSSIBLE";flag=1;break;}
    if(flag==0){
        cout<<"POSSIBLE"<<endl;
        for(int i=1;i<=n;i++) cout<<(scc[i]>scc[i+n])<<" ";
    }
    return 0;
}