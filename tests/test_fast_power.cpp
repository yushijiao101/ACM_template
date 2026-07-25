#include <bits/stdc++.h>
using namespace std;

#include "../template/math/fast_power.cpp"

long long naive_power(long long base, int exponent, long long mod) {
    base %= mod;
    if (base < 0) base += mod;
    long long result = 1 % mod;
    for (int i = 0; i < exponent; ++i) {
        result = static_cast<long long>((__int128)result * base % mod);
    }
    return result;
}

int main() {
    assert(mod_power(2, 10, 1000000007) == 1024);
    assert(mod_power(-2, 3, 5) == 2);
    assert(mod_power(123, 0, 1) == 0);

    mt19937_64 rng(20260719);
    for (int test = 0; test < 5000; ++test) {
        long long base = static_cast<long long>(rng());
        int exponent = rng() % 80;
        long long mod = rng() % 1000000000LL + 1;
        assert(mod_power(base, exponent, mod) == naive_power(base, exponent, mod));
    }
    return 0;
}
