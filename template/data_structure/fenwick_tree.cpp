/*
Algorithm: Fenwick Tree (Binary Indexed Tree)
Purpose: Point addition and prefix/range sum queries.
Complexity: O(log n) per update/query; O(n) space.
Indexing: 1-indexed, valid positions are [1, n].
Requirements: add() must never receive index 0; Value should hold all prefix sums.
Tested on: Not verified
Common mistakes: Updating index 0; mixing closed and half-open ranges; overflow in sums.
Status: Unverified
*/

#include <bits/stdc++.h>
using namespace std;

template <class Value = long long>
struct FenwickTree {
    int n = 0;
    vector<Value> tree;

    FenwickTree() = default;
    explicit FenwickTree(int n) { init(n); }

    void init(int n_) {
        n = n_;
        tree.assign(n + 1, Value{});
    }

    void add(int index, Value delta) {
        for (int i = index; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    Value prefix_sum(int index) const {
        Value result{};
        for (int i = index; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }

    Value range_sum(int left, int right) const {
        if (left > right) return Value{};
        return prefix_sum(right) - prefix_sum(left - 1);
    }
};
