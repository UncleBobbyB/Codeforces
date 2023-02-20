#include<bits/stdc++.h>
#include<numeric>

using namespace std;
#define pb push_back
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define pil pair<int, ll>
#define pll pair<ll, ll>
#define vi vector<int> 
#define vvi vector<vector<int> >
#define vl vector<ll>
#define vvl vector<vector<ll> > 
#define vpii vector<pii>
#define vpll vector<pll>
#define INF (1e9 + 10)
#define LLINF (1e18 + 10)

#define ari(n) array<int, n>
#define arl(n) array<ll, n>

#define all(x) (x).begin(), (x).end()
#define ue(x) (x).erase(unique(all((x))), (x).end())
#define SIZE(a) ((int)(a).size())


void err() { cout << "shit" << endl; exit(1); }

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(std::forward<Fun>(fun));
}


#ifdef LOCAL_DEBUG 
#include "local_debug.h"
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 
#endif

void solve();

int main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
#else
#ifdef LOCAL_DEBUG
    freopen("in", "r", stdin);
#endif
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed;
    cout.precision(10);

    int T;
    // cin >> T;
    T = 1;
    for (int i = 1; i <= T; i++) {
        // cout << "Case #" << i << ": ";
        solve();
    }
    return 0; 
}

void solve() {
}
