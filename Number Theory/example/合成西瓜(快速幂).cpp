#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
long long power(long long base, long long exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base*base) % MOD;
        exp /= 2;
    }
    return res;
}
void solve(){
    ll x,y;
    cin >> x >> y;
    ll cnt=1;
    if(x<=y) {cout<<1<<endl;return;}
    else{
        ll d=x-y-1;
        ll res=1;
        //calc 2^(d) * (y+1);
        res=power(2,d);
        res=res*(y+1);
        res%=MOD;
        cout<<res<<endl;
        return;
    }
    return;
}
signed main(){
    ll t;
    cin >> t;
    while(t--) solve();
}