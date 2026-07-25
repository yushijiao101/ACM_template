#include <bits/stdc++.h>
using namespace std;
vector<int> getnext(string P) {
    int M = P.length();
    vector<int> next(M, 0);
    int j=0;
    for (int i = 1; i < M; i++) {
        while (j > 0 && P[i] != P[j]) {
            j = next[j - 1]; 
        }
        if (P[i] == P[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}
vector<int> nxt;
vector<int> ans;
int main(){
    string s1,s2;
    cin >> s1 >> s2;
    int n1=s1.size();
    int n2=s2.size();
    nxt=getnext(s2);
    int j=0;
    for(int i=0;i<n1;i++){
    while(j>0&&s2[j]!=s1[i]) j=nxt[j-1];
    if(s1[i]==s2[j]) j++;
    if(j==n2) {ans.push_back(i-n2+2);j=nxt[j-1];}
    }
    for(auto it:ans) cout<<it<<endl;
    for(auto it:nxt) cout<<it<<" ";
}