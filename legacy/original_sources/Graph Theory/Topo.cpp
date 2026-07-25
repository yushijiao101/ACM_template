#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> son;
vector<int> in_d;
int main(){
   int n;
    cin >> n;
    son.resize(n+1);
    in_d.resize(n+1);
    for(int i=1;i<=n;i++){
        while(1){
            int a;
            cin >> a;
            if(a==0) break;
            else{
                son[i].push_back(a);
                in_d[a]++;
            }
        }
    }
    queue<int> q;
    unordered_set<int> st;
    for(int i=1;i<=n;i++) if(in_d[i]==0) {q.push(i);st.insert(i);}
    while(!q.empty()){
        int t=q.front();
        for(auto it:son[t]){
            in_d[it]--;
            if(in_d[it]==0) q.push(it);
        }
        cout<<t<<" ";
        q.pop();
    }
    return 0;
}