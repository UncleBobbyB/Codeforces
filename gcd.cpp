    auto gcd = y_combinator([&] (auto gcd, ll a, ll b) -> ll {
        if (a < b)
            swap(a, b);
        return b ? gcd(b, a%b) : a;
    });

    auto lcm = [&] (ll a, ll b) -> ll {
        return a * b / gcd(a, b);
    };

    auto inv = [&] (int b, int m) -> int {
        assert (gcd(b, m) == 1);
        assert (m > 1);
        int res = 1;
        for (int _ = 0; _ < m - 2; _++) 
            (res *= b) %= m;
        return res;
    };

    auto div = [&] (int a, int b) -> int {
        if (gcd(b, mod) != 1) 
            return (a % (b * mod)) / b % mod;
        return a * inv(b, mod) % mod;
    };

    auto pow = [&] (int a, int b) {
        if (!b)
            return 1;
        int ret = 1;
        while (b) {
            if (b&1)
                ret *= a;
            b >>= 1;
            a *= a;
        }
        return ret;
    };
