#include <bits/stdc++.h>
using namespace std;

#include "../template/data_structure/dsu.cpp"

int main() {
    constexpr int n = 40;
    DSU dsu(n);
    vector<int> naive(n);
    iota(naive.begin(), naive.end(), 0);

    mt19937 rng(20260719);
    for (int step = 0; step < 5000; ++step) {
        int x = rng() % n;
        int y = rng() % n;
        if (rng() & 1U) {
            int old_label = naive[y];
            int new_label = naive[x];
            dsu.unite(x, y);
            for (int& label : naive) {
                if (label == old_label) label = new_label;
            }
        } else {
            assert(dsu.same(x, y) == (naive[x] == naive[y]));
            int expected_size = count(naive.begin(), naive.end(), naive[x]);
            assert(dsu.component_size(x) == expected_size);
        }
    }
    return 0;
}
