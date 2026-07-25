#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Catalan(int n)
{
    ll catalan[n + 1];
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        catalan[i]=catalan[i-1]*(4*i-2)/(i+1);
    }
    return catalan[n];
}
int main()
{
    ll n;
    cin >> n;
    cout << Catalan(n);
    return 0;
}