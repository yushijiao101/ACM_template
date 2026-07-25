#include <bits/stdc++.h>
using namespace std;

// 32K字节的文件，最大节点数理论上不会超过 33000
// 开 40000 足够了，省内存且安全
const int N = 40005; 
int ch[N][26]; // 全局变量，避免栈溢出

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tot = 0;
    // 全局变量默认初始化为0，其实可以省掉 memset
    string s;

    while (cin >> s) {
        int u = 0;
        for (char c : s) {
            int idx = c - 'A'; 
            if (!ch[u][idx]) {
                ch[u][idx] = ++tot;
            }
            u = ch[u][idx];
        }
    }

    cout << tot + 1 << endl;
    return 0;
}