#include <bits/stdc++.h>    
using namespace std;
typedef long long ll;
const int MAX = 1e6+5;
vector<ll> primes;
ll is_prime[MAX];
void sieve() {
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i < MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j < MAX; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}
int main() {
    sieve();
    cout << primes[2024] << endl;
    return 0;
}
