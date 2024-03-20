// Karatsuba algorithm for fast multiplication of large numbers
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int get_digits(ll n)
{
    return n == 0 ? 1 : floor(log10(n)) + 1;
}

ll karatsuba(ll x, ll y)
{
    if (x < 10 || y < 10)
    {
        return x * y;
    }
    ll nx = get_digits(x);
    ll ny = get_digits(y);
    int n = max(nx, ny);
    int m = ceil(n / 2.0);
    ll p = pow(10, m);
    ll a = x / p;
    ll b = x % p;
    ll c = y / p;
    ll d = y % p;
    ll ac = karatsuba(a, c);
    ll bd = karatsuba(b, d);
    ll ad_plus_bc = karatsuba(a + b, c + d) - ac - bd;
    return ac * pow(10, 2 * m) + ad_plus_bc * pow(10, m) + bd;
}

int main()
{
    ll a, b;
    cin >> a;
    cin >> b;
    cout << karatsuba(a, b) << '\n';
}