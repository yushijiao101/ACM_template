#include <bits/stdc++.h>
using namespace std;

#include "../template/data_structure/fenwick_tree.cpp"

int main() {
    constexpr int n = 100;
    FenwickTree<long long> fenwick(n);
    vector<long long> values(n + 1);

    mt19937 rng(20260719);
    for (int step = 0; step < 10000; ++step) {
        if (rng() & 1U) {
            int index = rng() % n + 1;
            long long delta = static_cast<int>(rng() % 2001) - 1000;
            values[index] += delta;
            fenwick.add(index, delta);
        } else {
            int left = rng() % n + 1;
            int right = rng() % n + 1;
            if (left > right) swap(left, right);
            long long expected = accumulate(values.begin() + left,
                                            values.begin() + right + 1, 0LL);
            assert(fenwick.range_sum(left, right) == expected);
        }
    }
    return 0;
}
