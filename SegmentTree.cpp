// 0-indexed array, 1-indexed tree
vi L(n<<2), R(n<<2);
    vl sum_a(n<<2), lazy(n<<2);
    auto push_up = [&] (int o) {
        sum_a[o] = sum_a[o<<1] + sum_a[o<<1|1];
    };
    auto push_down = [&] (int o) {
        sum_a[o<<1] += lazy[o] * (R[o<<1] - L[o<<1] + 1);
        sum_a[o<<1|1] += lazy[o] * (R[o<<1|1] - L[o<<1|1] + 1);
        lazy[o<<1] += lazy[o], lazy[o<<1|1] += lazy[o];
        lazy[o] = 0;
    };
    y_combinator([&] (auto build, int o, int l, int r) -> void {
        L[o] = l, R[o] = r;
        if (l == r) {
            sum_a[o] = r ? a[r-1] : 0;
            return ;
        }
        int mid = (l + r) / 2;
        build(o<<1, l, mid);
        build(o<<1|1, mid + 1, r);
        push_up(o);
    }) (1, 0, n);
    auto modify = y_combinator([&] (auto modify, int o, int l, int r, ll d) -> void {
        if (L[o] > r || R[o] < l)
            return ;
        if (L[o] >= l && R[o] <= r) {
            sum_a[o] += d * (R[o] - L[o] + 1);
            lazy[o] += d;
            return ;
        }
        push_down(o);
        modify(o<<1, l, r, d);
        modify(o<<1|1, l, r, d);
        push_up(o);
    });
    auto query = y_combinator([&] (auto query, int o, int l, int r) -> ll {
        if (L[o] > r || R[o] < l)
            return 0;
        if (L[o] >= l && R[o] <= r)
            return sum_a[o];
        push_down(o);
        return query(o<<1, l, r) + query(o<<1|1, l, r);
    });