#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
int p[64];
int way[64];
vector<int> b;
int cnt;

void insert(int x){
    int val=x;

    int mask=1ULL<<cnt;

    for(int i=63;i>=0;i--){
        if(x>>i&1){
            if(p[i]){
                x^=p[i];
                mask^=way[i];
            }
            else{
                p[i]=x;
                way[i]=mask;
                b.push_back(val);
                cnt++;
                return;
            }
        }
    }
}

bool check(int x,int &mask){
    mask=0;

    for(int i=63;i>=0;i--){
        if(x>>i&1){
            if(!p[i]) return false;

            x^=p[i];
            mask^=way[i];
        }
    }

    return true;
}

void solve(){
    int k;
    cin >> n >> k;

    memset(p,0,sizeof(p));
    memset(way,0,sizeof(way));
    b.clear();
    cnt=0;

    for(int i=1;i<n;i++){
        insert(i);
    }

    int mask;
    int target=k^n;

    if(!check(target,mask)){
        cout << "NO"<<endl;
        return;
    }

    vector<int> vis(n,0);
    for(int i=0;i<cnt;i++){
        if(mask>>i&1){
            vis[b[i]]=1;
        }
    }

    cout << "YES"<<endl;
    for(int i=1;i<n;i++){
        if(!vis[i]) cout << i << ' ';
    }

    cout << 0 << ' ';
    for(int i=1;i<n;i++){
        if(vis[i]) cout << i << ' ';
    }

    cout << endl;
}

signed main(){
    int t;
    cin >> t;

    while(t--) solve();

    return 0;
}