#include<bits/stdc++.h>

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

void err() { cout << "shit" << endl; exit(1); }

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
void init();

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
    int n, m;
    cin >> n >> m;
    vl a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vi L(n<<2), R(n<<2);
    vl sum_d(n<<2), lazy(n<<2);
    auto push_up = [&] (int o) {
        sum_d[o] = sum_d[o<<1] + sum_d[o<<1|1];
    };
    auto push_down = [&] (int o) {
        sum_d[o<<1] += lazy[o] * (R[o<<1] - L[o<<1] + 1);
        sum_d[o<<1|1] += lazy[o] * (R[o<<1|1] - L[o<<1|1] + 1);
        lazy[o<<1] += lazy[o], lazy[o<<1|1] += lazy[o];
        lazy[o] = 0;
    };
    y_combinator([&] (auto build, int o, int l, int r) -> void {
        L[o] = l, R[o] = r;
        if (l == r) {
            sum_d[o] = r == 0 ? 0 : a[r] - a[r-1];
            return ;
        }
        int mid = (l + r) / 2;
        build(o<<1, l, mid), build(o<<1|1, mid + 1, r);
        push_up(o);
    }) (1, 0, n);
    auto query = y_combinator([&] (auto query, int o, int l, int r) -> ll {
        if (L[o] > r || R[o] < l)
            return 0;
        if (L[o] >= l && R[o] <= r)
            return sum_d[o];
        push_down(o);
        return query(o<<1, l, r) + query(o<<1|1, l, r);
    });
    auto modify = y_combinator([&] (auto modify, int o, int l, int r, int d) -> void {
        if (L[o] > r || R[o] < l)
            return ;
        if (L[o] >= l && R[o] <= r) {
            sum_d[o] += d * (R[o] - L[o] + 1);
            lazy[o] += d;
            return ;
        }
        push_down(o);
        modify(o<<1, l, r, d), modify(o<<1|1, l, r, d);
        push_up(o);
    });
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            ll k, d;
            cin >> l >> r >> k >> d;
            modify(1, l, l, k);
            modify(1, r + 1, r + 1, -k - (r - l) * d);
            if (r > l)
                modify(1, l + 1, r, d);
        } else {
            int p;
            cin >> p;
            cout << query(1, 1, p) << '\n';
        }
    }
}