#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
const int MAXN = 1e6 + 5; // 模式串总长度上限
    int trie[MAXN][26]; // Trie树，存储子节点编号
    int fail[MAXN];     // 失配指针
    int count[MAXN];    // 记录该节点作为单词结尾的次数（根据题目需求可改为标记/权值）
    int tot;            // 节点总数

    void init() {
        tot = 0;
    }

    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int i = ch - 'a';
            if (!trie[u][i]) {
                trie[u][i] = ++tot;
            }
            u = trie[u][i];
        }
        count[u]++; // 标记单词结尾
    }

    // 2. BFS 构建 fail 指针 (Trie Graph 优化版)
    void build() {
        queue<int> q;
        
        // 将根节点（0）的第一层子节点入队，它们的 fail 全部指向根节点
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
                    q.push(trie[u][i]);
                } else {
                    // 子节点不存在：直接向后看齐，连成图，极大简化查询时的各种 while 循环
                    trie[u][i] = trie[fail[u]][i];
                }
            }
        }
    }

    // 3. 多模式匹配查询（计算文本中有多少个模式串出现过）
    int query(const string& t) {
        int u = 0;
        int ans = 0;
        
        for (char ch : t) {
            int i = ch - 'a';
            u = trie[u][i]; // 由于构建了 Trie 图，这里直接跳转，不需要 while(u && !trie[u][i]) 

            // 沿着 fail 链把所有能匹配的后缀单词全部统计掉
            int temp = u;
            while (temp && count[temp] != -1) {
                ans += count[temp];
                count[temp] = -1; // 如果题目要求“不重复计算”，可以打上 -1 标记防止死循环/重复计数
                temp = fail[temp];
            }
        }
        return ans;
    }


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string pattern;
        cin >> pattern;
        insert(pattern);
    }
    build();
    string text;
    cin >> text;
    cout << query(text) << "\n";

    return 0;
}