#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;

vector<vector<ll>> multiply(ll n, vector<vector<ll>>& a, vector<vector<ll>>& b){
    vector<vector<ll>> ans(n,vector<ll>(n,0));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            for(ll k=0;k<n;k++){
                ans[i][j] += (a[i][k] * b[k][j]) % MOD; 
                ans[i][j] = ans[i][j] % MOD; 
            }
        }
    }
    return ans;
}


vector<vector<ll>> quick_power(ll n, vector<vector<ll>>& a, ll k){
    vector<vector<ll>> ans(n,vector<ll>(n,0));
    for(ll i=0;i<n;i++){
        ans[i][i]=1;
    }
    if(k == 0) return ans;
    while(k){
        if(k%2==1){
            ans=multiply(n,ans,a);
            k--;
        }
        else {
            a=multiply(n,a,a);
            k/=2;
        }
    }
    return ans;
}

int main() {
    long long n, k; 
    cin >> n >> k;
    vector<vector<ll>> a(n,vector<ll>(n,0)); 
    for(ll i=0;i<n;i++){ 
        for(ll j=0;j<n;j++){ 
            cin >> a[i][j];
            a[i][j]=a[i][j] % MOD; 
        }
    }
    vector<vector<ll>> ans=quick_power(n,a,k);
    for(ll i=0;i<n;i++){ 
        for(ll j=0;j<n;j++){
            cout << ans[i][j] % MOD << " "; 
        }
        cout << endl;
    }
    return 0;
}
