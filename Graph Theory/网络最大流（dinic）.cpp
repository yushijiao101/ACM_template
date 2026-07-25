 #include <bits/stdc++.h>
using namespace std;
       template<typename T> struct Flow_ {
    const int n;
    const T inf = numeric_limits<T>::max();
    struct Edge {
        int to;
        T w;
        Edge(int to, T w) : to(to), w(w) {}
   };
    vector<Edge> ver;
    vector<vector<int>> h;
    vector<int> cur, d;

    Flow_(int n) : n(n + 1), h(n + 1) {}
    void add(int u, int v, T c) {
        h[u].push_back(ver.size());
        ver.emplace_back(v, c);
        h[v].push_back(ver.size());
        ver.emplace_back(u, 0);
   }
    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto it : h[x]) {
                auto [y, w] = ver[it];
                if (w && d[y] == -1) {
                    d[y] = d[x] + 1;
                    if (y == t) return true;
                    q.push(y);
               }
           }
       }
        return false;
   }
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        auto r = f;
        for (int &i = cur[u]; i < h[u].size(); i++) {
            auto j = h[u][i];
            auto &[v, c] = ver[j];
            auto &[from, rc] = ver[j ^ 1];
            if (c && d[v] == d[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                c -= a;
                rc += a;
                r -= a;
                if (!r) return f;
           }
        }
        return f - r;
   }
    T work(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, inf);
       }
        return ans;
   }
};
int main(){
    int m,n;
    cin >> m >> n;
    using f=Flow_<long long>;
    f solve(n+2);
    while(1){
        int u1,v1;
        cin >> u1 >> v1;
        if(u1==-1&&v1==-1) break;
        solve.add(u1,v1,1);
    }
    for(int i=1;i<=m;i++) solve.add(0,i,1);
    for(int i=m+1;i<=n;i++) solve.add(i,n+1,1);
    cout<<solve.work(0,n+1)<<endl;
    for(int i=1;i<=m;i++){
        for(auto it:solve.h[i]){
            auto [v,w]=solve.ver[it];
            if(v!=0&&w==0) cout<<i<<" "<<v<<endl;
        }
    }
}