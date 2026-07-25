#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;
string s;
string get_min(string s){
    n=s.size()-1;
    for(int i=1;i<=n;i++){
        s+=s[i];
    }
    int i=1,j=2,k=0;
    while(i<=n&&j<=n&&k<=n){
        if(s[i+k]==s[j+k]){
            k++;
        }
        else{
            if(s[i+k]>s[j+k]) i+=k+1;
            else j+=k+1;
            if(i==j) j++;
            k=0;
        }
    }
    return s.substr(min(i,j),n);
}
int main(){
    cin >> n;
    string t;
    cin >> t;
    s.push_back(' ');
    s+=t;
    cout<<get_min(s)<<endl;
    return 0;

}