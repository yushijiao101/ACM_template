#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
    int n,t;
    cin >> n >> t;
    int f[n+1][20];
    for(int i=1;i<=n;i++) cin >> f[i][0];
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }
    while(t--){
    int l,r;
    l=read(),r=read();
    int j=log2(r-l+1);
    int ans=max(f[l][j],f[r-(1<<j)+1][j]);
    cout << ans << endl;
    }
    return 0;
}