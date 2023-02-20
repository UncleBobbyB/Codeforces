long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x - y), n);
    }
    return g;
}

void solve() {
    uint64 n;
    cin >> n;

    if (is_prime(n))
        cout << n << '\n';
    else 
        while (n > 1) {
            ll m = rho(n);
            cout << m << '\n';
            n /= m;
        }
}