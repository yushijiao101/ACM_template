#include <bits/stdc++.h>
using namespace std;

#include "../template/string/kmp.cpp"

int main() {
    assert((prefix_function("ababaca") == vector<int>{0, 0, 1, 2, 3, 0, 1}));
    assert((kmp_search("ababa", "aba") == vector<int>{0, 2}));
    assert((kmp_search("aaaa", "aa") == vector<int>{0, 1, 2}));
    assert(kmp_search("abc", "d").empty());
    assert(kmp_search("abc", "").empty());
    return 0;
}
