#include <bits/stdc++.h>
using namespace std;
const int N=105;
const int M=6005;
const int MOD=1e4+7;
int dp[N][M]; // dp[i][u]表示到第i个字符 匹配到了u节点的情况数
const int MAXN = 1e6 + 5; // 模式串总长度上限
    int trie[MAXN][26]; // Trie树，存储子节点编号
    int fail[MAXN];     // 失配指针
    int cont[MAXN];    // 记录该节点作为单词结尾的次数（根据题目需求可改为标记/权值）
    int tot;            // 节点总数

    void init() {
        tot = 0;
    }

    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int i = ch - 'A';
            if (!trie[u][i]) {
                trie[u][i] = ++tot;
            }
            u = trie[u][i];
        }
        cont[u]++; // 标记单词结尾
    }

    // 2. BFS 构建 fail 指针 (Trie Graph 优化版)
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (trie[0][i]) {
                fail[trie[0][i]] = 0;
                q.push(trie[0][i]);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 26; i++) {
                if (trie[u][i]) {
                    // 子节点存在：子节点的 fail 指向 (当前节点 fail 指向的节点的相同字符子节点)
                    fail[trie[u][i]] = trie[fail[u]][i];
                    cont[trie[u][i]] |= cont[trie[fail[u]][i]];
                    q.push(trie[u][i]);
                } else {
                    // 子节点不存在：直接向后看齐，连成图，极大简化查询时的各种 while 循环
                    trie[u][i] = trie[fail[u]][i];
                }
            }
        }
    }
int n,m;
int get(){
        int ans=1;
        for(int i=1;i<=m;i++){
            ans*=26;
            ans%=MOD;
        }
        return ans;
    }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string pattern;
        cin >> pattern;
        insert(pattern);
    }
    build();
    dp[0][0]=1;
    for (int i = 1; i <= m; i++) {         // 枚举文本串长度
    for (int u = 0; u <= tot; u++) {   // 枚举 AC 自动机上的所有合法节点
        if (cont[u] || !dp[i-1][u]) continue; // 如果当前节点是非法的，或者上一步不可达，跳过
        
        for (int c = 0; c < 26; c++) { // 枚举下一个放入的字符
            int v = trie[u][c];        // 利用 Trie 图直接获取下一个状态
            if (cont[v]) continue;    // 如果下一个状态包含模式串，不能转移过去
            
            dp[i][v] = (dp[i][v] + dp[i-1][u]) % MOD;
        }
    }
}

// 统计答案：长度为 m 时，到达所有合法的节点方案数之和
    int ans = 0;
    for (int u = 0; u <= tot; u++) {
        if (!cont[u]) {
            ans = (ans + dp[m][u]) % MOD;
        }
    }
    int temp=get();
    int res=(temp-ans+MOD)%MOD;
    cout<<res;
    return 0;
}