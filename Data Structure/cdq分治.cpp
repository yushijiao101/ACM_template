#include <bits/stdc++.h>
using namespace std;

struct Point {
    int idx;
    int x, y, z, w; // 增加 w 表示重复个数
};

vector<int> ans;
vector<int> cnt;
int n, k;
vector<int> tree(200005, 0);

int lowbit(int x) { return x & (-x); }

void update(int x, int y) {
    while (x <= k) {
        tree[x] += y;
        x += lowbit(x);
    }
}

int query(int x, int y) {
    int res = 0;
    while (y > 0) {
        res += tree[y];
        y -= lowbit(y);
    }
    x--;
    while (x > 0) {
        res -= tree[x];
        x -= lowbit(x);
    }
    return res;
}

void solve(vector<Point>& points) {
    int siz = points.size();
    if (siz <= 1) return;
    vector<Point> left, right;
    for (int i = 0; i < siz; i++) {
        if (i * 2 < siz) left.push_back(points[i]);
        else right.push_back(points[i]);
    }
    solve(left);
    solve(right);
    sort(left.begin(), left.end(), [](Point a, Point b) { return a.y < b.y; });
    sort(right.begin(), right.end(), [](Point a, Point b) { return a.y < b.y; });
    int l_ptr = 0;
    int r_ptr = -1;
    while (r_ptr < (int)right.size() - 1) {
        r_ptr++;
        while (l_ptr < (int)left.size() && left[l_ptr].y <= right[r_ptr].y) {
            update(left[l_ptr].z, left[l_ptr].w); // 这里加的是权重 w
            l_ptr++;
        }
        cnt[right[r_ptr].idx] += query(1, right[r_ptr].z);
    }
    for (int i = 0; i < l_ptr; i++) update(left[i].z, -left[i].w); // 这里减的也是权重 w
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); // 建议加上，防止大数据超时
    cin >> n >> k;
    ans.resize(n + 1, 0);
    cnt.resize(n + 1, 0);
    vector<Point> raw(n);
    for (int i = 0; i < n; i++) {
        cin >> raw[i].x >> raw[i].y >> raw[i].z;
    }
    
    // 1. 先排序，为了合并重复点
    sort(raw.begin(), raw.end(), [](Point a, Point b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });

    // 2. 加入 uni 逻辑，合并相同点
    vector<Point> uni;
    int same_cnt = 0;
    for (int i = 0; i < n; i++) {
        same_cnt++;
        if (i == n - 1 || raw[i].x != raw[i + 1].x || raw[i].y != raw[i + 1].y || raw[i].z != raw[i + 1].z) {
            uni.push_back({(int)uni.size(), raw[i].x, raw[i].y, raw[i].z, same_cnt});
            same_cnt = 0;
        }
    }

    solve(uni);

    // 3. 统计结果时，要把重复点自身的贡献(w-1)加上
    for (int i = 0; i < (int)uni.size(); i++) {
        ans[cnt[uni[i].idx] + uni[i].w - 1] += uni[i].w;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}