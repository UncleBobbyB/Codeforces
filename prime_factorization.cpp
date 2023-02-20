#define uint64 unsigned long long
#define max_uint64 (3e18 + 10)

/// Modular multiplication
/// @param a The first factor, a < m
/// @param a The second factor, b < m
/// @param m The modulus
/// @return The reduced product, a b mod m < m
uint64 mul(uint64 a, uint64 b, uint64 m)
{
        // Perform 128 multiplication and division
        uint64 q; // q = ⌊a b / m⌋
        uint64 r; // r = a b mod m
        asm("mulq %3;"
            "divq %4;"
            : "=a"(q), "=d"(r)
            : "a"(a), "rm"(b), "rm"(m));
        return r;
}

/// Modular exponentiation
/// @param b The base, b < m
/// @param e The exponent
/// @param m The modulus
/// @returns The reduced power of a, a^b mod m
uint64 pow(uint64 b, uint64 e, uint64 m)
{
        uint64 r = 1;
        for(; e; e >>= 1) {
                if(e & 1)
                        r = mul(r, b, m);
                b = mul(b, b, m);
        }
        return r;
}

/// Miller-Rabin probabilistic primality testing
/// @param n The number to test for  primality
/// @param k The witness for primality
/// @returns True iff when n is a k-stong pseudoprime
bool MillerRabin(uint64 n, uint64 k)
{
        // Factor n-1 as d*2^s
        uint64 s = 0;
        uint64 d = n - 1;
        for(; !(d & 1); s++)
                d >>= 1;

        // Verify x = k^(d 2^i) mod n != 1
        uint64 x = pow(k % n, d, n);
        if(x == 1 || x == n-1)
                return true;
        while(s-- > 1) {
                // x = x^2 mod n
                x = mul(x, x, n);
                if(x == 1)
                        return false;
                if(x == n-1)
                        return true;
        }
        return false;
}

template<typename T>
class Prime {

public:
    Prime() {}
    vector<T> is_prime;
    vector<T> primes;

    // maxn + 1
    vector<T> genPrime(int make_one, T maxn) {
        is_prime.resize(maxn, 1);
        is_prime[1] = make_one;
        is_prime[2] = 1;
        for (ll i = 2; i < maxn; i++)
            if (is_prime[i])
                for (ll j = 2 * i; j < maxn; j += i)
                    is_prime[j] = 0;
        // dbg(maxn, is_prime.size());
        for (ll i = 1; i < maxn; i++)
            if (is_prime[i])
                primes.pb(i);
        return primes;
    }
} ;

vector<uint64> prime_sieve(int maxn) {
    return Prime<uint64>().genPrime(0, maxn + 1);
}

const vector<uint64> small_primes = prime_sieve(1<<20);

/// Miller-Rabin probabilistic primality testing
/// @param n The number to test for  primality
/// @returns False when n is not a prime
bool is_prime(uint64 n)
{
        // Handle small primes fast
        for(int i = 0; i < small_primes.size(); i++) {
                uint64 p = small_primes[i];
                if(n == p)
                        return true;
                if(n % p == 0)
                        return false;
        }

        // Do a few Miller-Rabin rounds
        for(int i = 0; i < 10; i++)
                if(!MillerRabin(n, small_primes[i]))
                        return false;

        // Assume prime
        return true;
}

uint64 brent_pollard_factor(uint64 n) {
    const uint64 m = 1000;
    uint64 a, x, y, ys, r, q, g;
    do
        a = rand() % n;
        // a = random() % n;
    while(a==0||a==n-2);
    // y = random() % n;
    y = rand() % n;
    r = 1;
    q = 1;

    do {
        x = y;
        for(uint64 i=0; i < r; i++) {
                        // y = y² + a mod n
            y = mul(y, y, n);
            y += a;
            if(y < a)
                y += (max_uint64 - n) + 1;
            y %= n;
        }

        uint64 k =0;
        do {
            for(uint64 i=0; i < m && i < r-k; i++) {
                ys = y;

                                // y = y² + a mod n
                y = mul(y, y, n);
                y += a;
                if(y < a)
                    y += (max_uint64 - n) + 1;
                y %= n;

                                // q = q |x-y| mod n
                q = mul(q, (x>y)?x-y:y-x, n);
            }
            g = gcd(q, n);
            k += m;
        } while(k < r && g == 1);

        r <<= 1;
    } while(g == 1);

    if(g == n) {
        do {
                        // ys = ys² + a mod n
            ys = mul(ys, ys, n);
            ys += a;
            if(ys < a)
                ys += (max_uint64 - n) + 1;
            ys %= n;

            g = gcd((x>ys)?x-ys:ys-x, n);
        } while(g == 1);
    }

    return g;
}

vector<uint64> prime_factors(uint64 n)
{
    vector<uint64> factors;
    vector<uint64> primes;

    if (is_prime(n)) {
        return {n};
    }

    uint64 factor = brent_pollard_factor(n);
    factors.pb(n / factor);
    factors.pb(factor);

    do {
        uint64 m = factors[factors.size() - 1];
        factors.pop_back();

        if(m == 1)
            continue;

        if(is_prime(m)) {
            primes.pb(m);

                        // Remove the prime from the other factors
            for(int i=0; i < factors.size(); i++) {
                uint64 k = factors[i];
                if(k % m == 0) {
                    do
                        k /= m;
                    while(k % m == 0);
                    factors[i] = k;
                }
            }
        } else {
            // factor = (m < 100) ? small_factor(m) : brent_pollard_factor(m);
            factor = brent_pollard_factor(m);
            factors.pb(m / factor);
            factors.pb(factor);
        }
    } while(factors.size());

    return primes;
}

vector<uint64> duplicated_prime_factors(uint64 n) {
    auto primes = prime_factors(n);
    vector<uint64> d_primes;
    for (auto p : primes) 
        while (n % p == 0) 
            d_primes.pb(p), n /= p;
    return d_primes;
}


void solve() {
    uint64 n;
    cin >> n;

    // dbg(prime_factors(n));
    dbg(duplicated_prime_factors(n));
}
