int main {
    vi c, cnt;
    vvi ch;
    c.pb(0), ch.pb({}), cnt.pb(0);
    auto insert = [&] (string s) {
        cnt[0]++;
        for (int i = 0, cur = 0; i < (int)s.length(); i++) {
            int ok = 0;
            for (int j : ch[cur]) 
                if (c[j] == s[i] - 'a') {
                    ok = 1, cur = j;
                    break;
                }
            if (!ok)
                ch[cur].pb(c.size()), cnt.pb(0), cur = c.size(), ch.pb({}), c.pb(s[i] - 'a');
            cnt[cur]++;
            assert(ch.size() == c.size());
        }
    };
    auto query = [&] (string t) -> int {
        int cur = 0;
        for (int i = 0; i < (int)t.length(); i++) {
            int ok = 0;
            for (int j : ch[cur])
                if (c[j] == t[i] - 'a') {
                    ok = 1, cur = j;
                    break;
                }
            if (!ok)
                return 0;
        }
        return cnt[cur];
    };

    return 0;
}