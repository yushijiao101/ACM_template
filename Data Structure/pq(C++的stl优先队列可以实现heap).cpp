#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
void solve() {
    // 优化标准输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    priority_queue<int> pq;
    for(int i=1;i<=n;i++){
        int op;
                         cin >> op;
                         if(op==1){
                           int x;
                             cin >>x;
                             pq.push(x);
                         }
        else if(op==2){
            cout<<pq.top()<<endl;
        }
        else{
            pq.pop();
            
        }
                         }
}

signed main() {
    solve();
    return 0;
}