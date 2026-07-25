//FIB NIM 
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int L=100;
const int N=1e15+5;
int fib[L];
void build(){
    fib[1]=1;
    fib[2]=2;
    fib[3]=3;
    for(int i=4;i<=L;i++){
        if(fib[i-1]>N) break;
        else fib[i]=fib[i-1]+fib[i-2];
        }
    return;
}
int val;
int dcp(){
    vector<int> v;
    for(int i=L;i>=1;i--){
        if(fib[i]!=0&&fib[i]<=val) {val=val-fib[i];v.push_back(fib[i]);}    
        if(val==0) break;
    }
    int n=v.size();
    return v[n-1];
}
signed main(){
    build();
    cin >> val;
    cout<<dcp();
}