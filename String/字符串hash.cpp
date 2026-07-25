#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int P = 131;
const int N = 1e6+10;
ull p[N],h[N];
int n;
void init(){
    p[0]=1;
    h[0]=0;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*P;
        h[i]=h[i-1]*P+s[i];
    }
}
ull get(int l,int r){
    return h[r]-h[l-1]*p[r-l+1];
}
bool substr_equal(int l1,int r1,int l2,int r2){
    return get(l1,r1)==get(l2,r2);
}