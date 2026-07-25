#include <bits/stdc++.h>
using namespace std;
const int N=3*1e6+5;
int trie[N][64];
int val[N];
int tot=0;
int getnum(char x){
    if(x>='A'&&x<='Z')
        return x-'A';
    else if(x>='a'&&x<='z')
        return x-'a'+26;
    else
        return x-'0'+52;
} 

void insert(string s){
    int node=0;
    val[node]++;
    int t=s.size();
    for(int i=0;i<t;i++){
        int c=getnum(s[i]);
        if(trie[node][c]==0) trie[node][c]=++tot;
        node=trie[node][c];
        val[node]++;
    }
}
int query(string s){
    int node=0;
    int t=s.size();
    for(int i=0;i<t;i++){
        int c=getnum(s[i]);
        if(trie[node][c]==0) return 0;
        node=trie[node][c];
    }
    return val[node];
}
signed main(){
    int t;cin >> t;
    while(t--){
    for(int i = 0; i <= tot; i++) {
        val[i] = 0;
    for(int j = 0; j < 63; j++) {
        trie[i][j] = 0;
        }
    }
        tot = 0;
        int n,q;
        cin >> n >> q;
        for(int i=1;i<=n;i++){
            string s;cin >> s;
            insert(s);
        }
        for(int i=1;i<=q;i++){
            string t;
            cin >> t;
            cout<<query(t)<<endl;
        }
    }
    return 0;
}    
