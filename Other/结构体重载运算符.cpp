#include <bits/stdc++.h>
using namespace std;
struct node{
int x,y,z;
};
struct cmp{
    bool operator()(const node& a, const node& b){
        if (a.x != b.x) {
        return a.x < b.x; 
        }
        // 如果 x 相等，按 y 排
        return a.y < b.y;
    }
};
priority_queue<node,vector<node>,cmp> pq;
int main(){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        int x,y,z;
        cin >> x >> y >> z;
        pq.push({x,y,z});
    }
    cout<<pq.top().x<<" "<<pq.top().y<<" "<<pq.top().z;
}