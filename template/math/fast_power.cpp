/*
Algorithm: Binary modular exponentiation
Purpose: Compute base^exponent modulo mod.
Complexity: O(log exponent) time; O(1) extra space.
Indexing: Not applicable.
Requirements: exponent >= 0 and mod > 0; GNU++17 (__int128 is used).
Tested on: Not verified
Common mistakes: Overflow before modulo; negative-base normalization; mod equal to 1.
Status: Unverified
*/

#include <bits/stdc++.h>
using namespace std;

long long mod_power(long long base, long long exponent, long long mod) {
    assert(exponent >= 0 && mod > 0);
    base %= mod;
    if (base < 0) base += mod;

    long long result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1LL) {
            result = static_cast<long long>((__int128)result * base % mod);
        }
        base = static_cast<long long>((__int128)base * base % mod);
        exponent >>= 1;
    }
    return result;
}
