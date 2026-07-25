#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N= 1e6+5;
int b_s;
int sum=0;
int a[N]; // 原数组
int cnt[N];  // cnt[i] 记录区间内i出现的次数
void add(int x){
sum-=x*cnt[x]*cnt[x];
cnt[x]++;
sum+=x*cnt[x]*cnt[x];
}
void del(int x){
sum-=x*cnt[x]*cnt[x];
cnt[x]--;
sum+=x*cnt[x]*cnt[x];
}
struct query{
    int l,r,id;//id是表示第几次查询
    bool operator<(const query& o){
        int s1=l/b_s;        // b_s为block size 分块的大小
        int s2=o.l/b_s;
        if(s1!=s2) return s1<s2;
        else {
            if(s1&1) return r<o.r;
            else return r>o.r;
            }
    }
}q[N];
void solve(){
    int n,t;
    cin >> n >> t;
    b_s=sqrt(n);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
	for(int i=1;i<=t;i++){
	    int l,r;
	    cin >> l >> r;
	    q[i]={l,r,i};
	}
	vector<int> ans(t+1);
	sort(q+1,q+t+1);
	for(int i=1,l=1,r=0;i<=t;i++){
	while(l>q[i].l) add(a[--l]);//左扩展
	while(r<q[i].r) add(a[++r]);//右扩展
	while(l<q[i].l) del(a[l++]);//左删除
	while(r>q[i].r) del(a[r--]);//右删除
	//现在得到的是排序后的查询的答案 我们要把他还原成排序前
	ans[q[i].id]=sum;
	}
	for(int i=1;i<=t;i++) cout<< ans[i]<<endl;
}
signed main(){
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}