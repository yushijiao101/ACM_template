#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pvi pair<vector<ld>,int>
const ld eps = 1e-5;
int n,m;
vector<vector<ld>> p(501,vector<ld>(501,0));
int ans=0;
int cnt=0;
void insert(vector<ld> &t,int val){
    int sz=t.size();
    for(int i=0;i<sz;i++){
        if(fabs(t[i])>eps){  //向量的第i位存在
            if(fabs(p[i][i])>eps){ //x^=p[i];    //p[i]已经存在
                ld r=t[i]/p[i][i];
                //i+1位后面的都减去ratio倍的
                for(int j=i+1;j<sz;j++) t[j]-=(p[i][j]*r);
                }
            else {p[i]=t;cnt++;ans+=val;break;}
        }
    }
}
vector<pvi> v(501);
signed main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        vector<ld> temp;
        for(int j=0;j<m;j++){
            ld t;
            cin >> t;
        temp.push_back(t);
        }
        v[i].first=temp;
    }
    for(int i=0;i<n;i++) {
        int val;cin >> val;
        v[i].second=val;
    }
    sort(v.begin(),v.begin()+n,[](const pvi &a,const pvi &b){
        return a.second<b.second;
    });
    for(int i=0;i<n;i++){
        auto [t,val] = v[i];
        insert(t,val);
    }
    cout<<cnt<<" "<<ans;
}