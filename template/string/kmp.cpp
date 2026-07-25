/*
Algorithm: Knuth-Morris-Pratt (KMP) string matching
Purpose: Find every occurrence of a non-empty pattern in a text.
Complexity: O(|text| + |pattern|) time; O(|pattern|) extra space.
Indexing: Strings and returned match positions are 0-indexed.
Requirements: The pattern should be non-empty; comparisons use exact char equality.
Tested on: Not verified
Common mistakes: Forgetting fallback after a match and missing overlapping occurrences.
Status: Unverified
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& pattern) {
    vector<int> prefix(pattern.size());
    for (int i = 1, matched = 0; i < static_cast<int>(pattern.size()); ++i) {
        while (matched > 0 && pattern[i] != pattern[matched]) {
            matched = prefix[matched - 1];
        }
        if (pattern[i] == pattern[matched]) ++matched;
        prefix[i] = matched;
    }
    return prefix;
}

vector<int> kmp_search(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty()) return matches;

    vector<int> prefix = prefix_function(pattern);
    for (int i = 0, matched = 0; i < static_cast<int>(text.size()); ++i) {
        while (matched > 0 && text[i] != pattern[matched]) {
            matched = prefix[matched - 1];
        }
        if (text[i] == pattern[matched]) ++matched;
        if (matched == static_cast<int>(pattern.size())) {
            matches.push_back(i - static_cast<int>(pattern.size()) + 1);
            matched = prefix[matched - 1];
        }
    }
    return matches;
}
