class Graph {
private:
    class Edge {

    public:
        int from, to, rev;
        ll cap;
        Edge (int from, int to, ll cap, int rev) {
            this->from = from, this->to = to, this->cap = cap, this->rev = rev;
        };
   };

public:
    int n, m;
    vector<Edge> edges;
    vvi g;
    vector<map<int, int>> mark;

    Graph(int n, int m) {
        this->n = n, this->m = m;
        g = vvi(n);
        mark = vector<map<int, int>> (n);
    }

    void add (int u, int v, int c) {
        if (u == n || v == n)
            n++, g.pb({}), mark.pb({});
        mark[u][v] = mark[v][u] = 1;
        g[u].pb(edges.size());
        edges.pb(Edge(u, v, c, (int)edges.size() + 1));
        g[v].pb(edges.size());
        edges.pb(Edge(v, u, 0, (int)edges.size() - 1));
    };


    ll MaxFlow (int s, int t) { 
        if (1ll * n * n < 1ll * m * m * m) 
            return HLPP(s, t); // O(n ^ 2 * sqrt(m)
        if (n < m)
            return Dicnic(s, t); // O(n^2 * m)
        return EK(s, t); // O(n * m ^ 2)
    };

private:

    ll FordFulkerson (int s, int t) {
        vi vis(n);
        auto dfs = y_combinator([&] (auto dfs, ll f, int u) -> ll {
            if (u == t) 
                return f;
            vis[u] = 1;
            for (int e : g[u]) {
                auto& edge = edges[e];
                if (!vis[edge.to] && edge.cap > 0) {
                    ll d = dfs(min(f, edge.cap), edge.to);
                    if (d > 0) {
                        edge.cap -= d;
                        edges[edge.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }) ;
        ll max_flow = 0;
        for (int flow = dfs(INF, s); flow > 0; fill(all(vis), 0), flow = dfs(INF, s))
            max_flow += 1ll * flow; 
        return max_flow;
    };

    ll EK (int s, int t) {
        vi pre(n, -1);
        vl flow(n);
        flow[s] = LLINF;
        auto bfs = [&] (int s, int t) -> ll {
            queue<int> qu;
            qu.push(s);
            while (!qu.empty()) {
                int u = qu.front(); 
                qu.pop();
                if (u == t) 
                    break;
                for (int i : g[u]) {
                    Edge& e = edges[i];
                    if (e.to != s && e.cap > 0 && pre[e.to] == -1) 
                        pre[e.to] = i, flow[e.to] = min(flow[u], e.cap), qu.push(e.to);
                }
            }
            if (pre[t] == -1) 
                return 0;
            return flow[t];
        };
        ll sum_flow = 0;
        for (int flow = bfs(s, t); flow > 0; fill(all(pre), -1), flow = bfs(s, t)) {
            for (int i = pre[t]; ~i; i = pre[edges[i].from]) 
                edges[i].cap -= flow, edges[edges[i].rev].cap += flow;
            sum_flow += flow;
        }
        return sum_flow;
    };

    ll Dicnic (int s, int t) {
        vi dist(n);
        auto bfs  = [&] () -> void {
            queue<int> qu;
            qu.push(s);
            dist[s] = 0;
            while (!qu.empty()) {
                int u = qu.front();
                qu.pop();
                for (int i : g[u]) {
                    Edge& e = edges[i];
                    if (e.cap > 0 && dist[e.to] == -1) 
                        dist[e.to] = dist[u] + 1, qu.push(e.to);
                }
            }
        };
        vi vis(n);
        auto dfs = y_combinator([&] (auto dfs, ll flow, int u) -> ll {
            if (u == t)
                return flow;
            vis[u] = 1;
            ll res = 0;
            for (int i : g[u]) {
                Edge& e = edges[i];
                if (dist[e.to] != dist[u] + 1 || vis[e.to] || e.cap <= 0)
                    continue;
                ll d = dfs(min(flow, e.cap), e.to);
                if (d > 0) 
                    e.cap -= d, edges[e.rev].cap += d, flow -= d, res += d;
            }
            return res;
        });
        auto find_aug = [&] () -> ll {
            fill(all(dist), -1);
            bfs();
            fill(all(vis), 0);
            return dfs(LLINF, s);
        };
        ll sum_flow = 0;
        for (ll flow = find_aug(); flow > 0; flow = find_aug())
            sum_flow += flow;
        return sum_flow;
    };


    ll HLPP(int s, int t) {
        vl rem(n);
        auto pushFlow = [&] (Edge& e) -> int {
            ll d = min(rem[e.from], e.cap);
            e.cap -= d;
            edges[e.rev].cap += d;
            rem[e.from] -= d;
            rem[e.to] += d;
            return d;
        };
        vi dist(n), gap(n + m);
        priority_queue<int, vi, function<bool(int, int)>> qu([&] (int i, int j) { return dist[i] < dist[j]; });
        dist[s] = n, rem[s] = LLINF, gap[n] = 1, gap[0] = n - 1;
        qu.push(s);

        auto makeGap = [&] (int d) -> void {
            for (int u = 0; u < n; u++)
                if (u != s && u != t && dist[u] > d && dist[u] <= n) dist[u] = n + 1;
        };

        while (!qu.empty()) {
            int u = qu.top();
            qu.pop();
            if (!rem[u])
                continue;
            for (int i : g[u]) {
                Edge& e = edges[i];
                if ((u == s || dist[u] == dist[e.to] + 1) && pushFlow(e) && e.to != s && e.to != t) 
                    qu.push(e.to);
            }
            if (rem[u] && u != s && u != t) {
                if (!--gap[dist[u]])
                    makeGap(dist[u]);
                ++gap[++dist[u]];
                qu.push(u);
            }
        }
        return rem[t];
    };
};
