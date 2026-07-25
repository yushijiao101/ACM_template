// // 返回值定义: 1 = 唯一解, 0 = 无穷多解, -1 = 无解
// int Gauss() {
//     int row = 1; // 当前正在处理第几行
//     for (int col = 1; col <= n; col++) {
//         // 1. 找当前列绝对值最大的行
//         int t = row;
//         for (int i = row + 1; i <= n; i++)
//             if (abs(a[i][col]) > abs(a[t][col])) t = i;

//         // 2. 如果这一列全剩下0了，跳过这一列处理下一列变量（说明有自由元）
//         if (abs(a[t][col]) < eps) continue;

//         // 3. 交换并消元
//         swap(a[t], a[row]);
//         double div = a[row][col];
//         for (int j = col; j <= n + 1; j++) a[row][j] /= div;
//         for (int i = 1; i <= n; i++) {
//             if (i != row) {
//                 double mul = a[i][col];
//                 for (int j = col; j <= n + 1; j++)
//                     a[i][j] -= a[row][j] * mul;
//             }
//         }
//         row++; // 只有找到了主元，才处理下一行
//     }

//     // 4. 判定结果
//     if (row <= n) { // 说明主元个数小于 n
//         for (int i = row; i <= n; i++) {
//             // 如果系数全是0，但常数项不是0，则无解
//             if (abs(a[i][n + 1]) > eps) return -1; 
//         }
//         return 0; // 否则是无穷多解
//     }
//     return 1; // 唯一解
// }

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const int maxN = 105;
double a[maxN][maxN];
int n;

bool Gauss() {
    for (int i = 1; i <= n; i++) {
        int t = i;
        for (int j = i + 1; j <= n; j++) {
            if (abs(a[j][i]) > abs(a[t][i])) {
                t = j;
            }
        }
        if (t != i) swap(a[i], a[t]);
        if (abs(a[i][i]) < eps) return false;
        double div = a[i][i];
        for (int j = i; j <= n + 1; j++) {
            a[i][j] /= div;
        }
        for (int k = 1; k <= n; k++) {
            if (k != i) {
                double mul = a[k][i];
                for (int j = i; j <= n + 1; j++) {
                    a[k][j] -= a[i][j] * mul;
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> a[i][j];
        }
    }

    if (Gauss()) {
        for (int i = 1; i <= n; i++) {
            cout << fixed << setprecision(2) << a[i][n + 1] << endl;
        }
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}