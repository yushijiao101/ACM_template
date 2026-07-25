/*
Algorithm: Disjoint Set Union (DSU) with path compression and union by size
Purpose: Maintain connectivity and component sizes under merge operations.
Complexity: Amortized O(alpha(n)) per find/unite; O(n) space.
Indexing: 0-indexed, valid vertices are [0, n - 1].
Requirements: The number of vertices is fixed after init; inputs must be in range.
Tested on: Not verified
Common mistakes: Mixing 0/1-indexing; forgetting to reinitialize between test cases.
Status: Unverified
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU() = default;
    explicit DSU(int n) { init(n); }

    void init(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int component_size(int x) {
        return size[find(x)];
    }
};
