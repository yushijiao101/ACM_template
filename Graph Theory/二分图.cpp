#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
struct edge{
    int v,ne;
}e[N];
int h[N];
int idx;
int color[N];
void add(int u,int v){
    e[++idx] = {v,h[u]};
    h[u] = idx;
}
bool dfs(int u,int c){
    color[u] = c;
    for(int i = h[u];i;i = e[i].ne){
        int v = e[i].v;
        if(color[v] == -1){
            if(dfs(v,3-c)) return 1;
        }
        else if(color[v] == c) return 1;
    }
    return 0;
}
int n,m;
int main(){
    cin >> n >> m;
    for(int i = 0;i < m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    bool flag = true;
    for(int i = 1;i <= n;i++){
        if(color[i] == -1){
            if(dfs(i,1)){
                flag = false;
                break;
            }
        }
    }
    if(flag) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}