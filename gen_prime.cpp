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
