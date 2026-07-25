#include <bits/stdc++.h>
using namespace std;
int n;//节点数
vector<int> subtree_size(n+1);
vector<vector<int>> adj;      // 邻接表
int bfs(int root,int fa){
    for(auto it:adj[root]){
        if(it!=fa){
            subtree_size[root]+=bfs(it,root);
        }
        return subtree_size[root]+1;
    }
}