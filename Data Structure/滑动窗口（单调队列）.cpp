#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n,k;
    cin >> n >> k;
    vector<long long> a(n+1);
    for(long long i=1;i<=n;i++) cin >> a[i];
    //deque实现 简单理解
    // deque<long long> dq1;//单增
    // deque<long long> dq2;//单减
    // vector<long long> res1;
    //     vector<long long> res2;
    // for(long long i=1;i<=n;i++){
    //     long long num=a[i];
    //     while(!dq1.empty()&&a[dq1.front()]>num) dq1.pop_front();
    //         dq1.push_front(i);
    //     if(i>=k&&dq1.back()==i-k) dq1.pop_back();
    //     if(i>=k) res1.push_back(dq1.back());
    //     while(!dq2.empty()&&a[dq2.front()]<num) dq2.pop_front();
    //         dq2.push_front(i);
    //             if(i>=k&&dq2.back()==i-k) dq2.pop_back();
    //     if(i>=k) res2.push_back(dq2.back());
    // }
    // for(auto it:res1) cout<<a[it]<<" ";
    // cout<<endl;
    //     for(auto it:res2) cout<<a[it]<<" ";
    vector<long long> res1(n+1);
    vector<long long> res2(n+1);
    int l = 1, r = 0;
    vector<long long> q1(n+1);
    vector<long long> q2(n+1);
    for (int i = 1; i <= n; i++) {
    while (l <= r && a[q1[r]] >= a[i]) r--;
    q1[++r] = i;
    if (q1[l] <= i - k) l++;
    if (i >= k) res1[i] = a[q1[l]];
}
l = 1;
r = 0;
        for (int i = 1; i <= n; i++) {
    while (l <= r && a[q2[r]] <= a[i]) r--;
    q2[++r] = i;
    if (q2[l] <= i - k) l++;
    if (i >= k) res2[i] = a[q2[l]];
}
    for(int i=k;i<=n;i++) cout<<res1[i]<<" ";
       cout<<endl;
    for(int i=k;i<=n;i++) cout<<res2[i]<<" ";
    return 0;
}