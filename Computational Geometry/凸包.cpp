#include <bits/stdc++.h>
using namespace std;

struct point {
    double x;
    double y;
};

// 向量 (a->b) 和 (a->c) 的叉积
double cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmp(point a, point b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    if (n < 3) {
        cout << 0 << "\n";
        return 0;
    }

    vector<point> coor(n);
    for (int i = 0; i < n; i++) {
        cin >> coor[i].x >> coor[i].y;
    }

    sort(coor.begin(), coor.end(), cmp);

    vector<point> hull;

    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), coor[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(coor[i]);
    }

    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), coor[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(coor[i]);
    }

    double ans = 0;
    for (size_t i = 0; i < hull.size() - 1; i++) {
        ans += dist(hull[i], hull[i + 1]);
    }

    cout << fixed << setprecision(2) << ans << "\n";

    return 0;
}