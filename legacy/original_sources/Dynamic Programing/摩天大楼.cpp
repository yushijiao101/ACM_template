#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=103;
const int L=1003;
const int M=1e9+7;
int dp[N][N][L][3];
int a[N];
int d[N];
signed main(){
    memset(dp,0,sizeof(dp));
    dp[0][0][0][0]=1;
    int n,l;
    cin >> n >> l;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        d[i]=a[i]-a[i-1];
    }    
    if(n==1) {cout<<1;return 0;}
    for(int c=1;c<=n;c++){

        for(int i=0;i<=n;i++){
            for(int val=0;val<=l;val++){
                for(int k=0;k<=2;k++){
                    
                    if(dp[c-1][i][val][k]>0){
                    dp[c-1][i][val][k]%=M;
                    int b=dp[c-1][i][val][k];
                    dp[c][i+1][min(val+(2*i-k)*d[c],l+1)][k]+=b*(i+1-k)%M; //占据非端点 两端都没有点
                    if(i>=1) dp[c][i][min(val+(2*i-k)*d[c],l+1)][k]+=b*(2*i-k)%M; //占据非端点 只有一端都有点
                    if(i>=2) dp[c][i-1][min(val+(2*i-k)*d[c],l+1)][k]+=b*(i-1)%M; //占据非端点 两端都有点
                        
                        if(k!=2){
                    dp[c][i+1][min(val+(2*i-k)*d[c],l+1)][k+1]+=b*(2-k)%M;  //占端点 且旁边没点
                    if(i>=1) dp[c][i][min(val+(2*i-k)*d[c],l+1)][k+1]+=b*(2-k)%M;  //占端点 旁边有点
                            }
                        
                    }
                }
            }
        }

    }
    int ans=0;
    for(int j=0;j<=l;j++) {ans+=dp[n][1][j][2]%M;ans%=M;}
    cout<<ans;
return 0;
}