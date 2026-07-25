#include <iostream>
#include <vector>
using namespace std;
vector<int> fa(30001);
vector<int> dis(30001,0);
int find(int a) {
    if (fa[a] == a) return a;
    else{
        int root = find(fa[a]);
        dis[a] += dis[fa[a]];
        fa[a] = root;
        return root;
    }  
    return  a;
}
int main() {
    int T;
    cin >> T;
    int n=30000;
    vector<int> num(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    for (int i = 1; i <= T; i++) {
    char  a;
            int b, c;
        cin >> a >> b >> c;
            int rootB = find(b);
            int rootC = find(c);
            //int p=find(3);  
            //if(i==3) cout<<dis[3]<<" "<<dis[4]<<" "<<dis[5]<<endl;
            if(a=='M'){
            if (rootB != rootC) {
                fa[rootB] = rootC; 
                dis[rootB] = num[rootC];
                num[rootC]+=num[rootB];
            }
            }
            else{
                if(rootB!=rootC) cout<<-1<<endl;
                else{
                    cout<<abs(dis[b]-dis[c])-1<<endl;
                }
            }

    }

    return 0;
}