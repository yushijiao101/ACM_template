#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=20;
int a[N];
int f[N][10];
void init(){
for(int i=0;i<=9;i++) f[1][i]=1;
	for(int i=2;i<=18;i++)	//处理到了第i位
		for(int j=0;j<=9;j++)	//枚举最高位的数字j
			for(int k=0;k<=9;k++)
				if(abs(k-j)>=2) f[i][j]+=f[i-1][k];
return;
}
int dp(int x){
    if(!x) return 0;
    int cnt=0;//记录数位
    while(x){
    a[++cnt]=x%10;
    x/=10;
    }
    int res=0,last=-2;  //last表示上一位数字
    for(int i=cnt;i>=1;i--){
    	int now=a[i];//now表示当前位数字
    	for(int j=(i==cnt);j<now;j++) //最高位不能是0 这里的(i==cnt)写的很好
    	if(abs(j-last)>=2) res+=f[i][j];
    	
    	if(abs(last-now)<2) break;//如果这个时候出现矛盾 就不需要继续分类讨论了 后面的都是错 因为此时的第i位不能是now
    	last=now;
        if(i == 1) res++;
    }
    for(int i=1;i<cnt;i++)
        for(int j=1;j<=9;j++) res+=f[i][j];
    return res;
}
signed main(){
    init();
    int l,r;
    cin >> l >> r;
    cout<<dp(r)-dp(l-1);
    return 0;
}