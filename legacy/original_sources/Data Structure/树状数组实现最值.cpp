#include <bits/stdc++.h>
using namespace std;
int n;
int tree[100005];
int lowbit(int x) { return x & (-x); }
void update(int x,int y){
    while(x>=1){
        tree[x]=max(tree[x],y);
        x-=lowbit(x);
    }
}
void query(int x){//求x->n的最大值
    int res=0;
    while(x<=n){
        res=max(res,tree[x]);
        x+=lowbit(x);
    }       
    cout<<res<<endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        tree[i] = max(tree[i], val) ;
        int j = i + lowbit(i);
        if (j <= n) tree[j] = max(tree[j], tree[i]);
    }
    while(m--){
        int a;
        cin >>a;
        int x,y;
        cin >> x >> y;
        if(a==1){
            update(x,y);
        }
        else if(a==2){
            query(x);
        }
    }
    return 0;
}