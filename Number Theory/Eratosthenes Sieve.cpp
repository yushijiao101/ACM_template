#include <bits/stdc++.h>
// 时间复杂度 O(MX * log log MX)
const int MX = 1'000'001;

bool is_prime[MX];

vector<int> primes;

    fill(is_prime, is_prime + MX, true);

    is_prime[0] = is_prime[1] = false; // 0 和 1 不是质数

    for (int i = 2; i < MX; i++) {

        if (is_prime[i]) {

            primes.push_back(i);

            for (long long j = 1LL * i * i; j < MX; j += i) {

                is_prime[j] = false; // j 是质数 i 的倍数

            }
        }
    }


    