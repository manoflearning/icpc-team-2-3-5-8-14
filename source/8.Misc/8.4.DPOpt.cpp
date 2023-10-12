// Knuth Optimization
// Recurrence: DP[i][j] = min(DP[i][k] + DP[k + 1][j]) + C[i][j] (i <= k < j)
// Condition: C[i][j] is a monge array (satisfies C[a][c] + C[b][d] <= C[a][d] + C[b][c]),
//            and satisfies C[a][d] >= C[b][c] for a <= b <= c <= d
// Naive Complexity: O(n^3)
// Optimized Complexity: O(n^2)

// Let opt[i][j] be the value of k that minimizes DP[i][j]
// The following holds: opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]

// BOJ 13974 AC Code
// https://www.acmicpc.net/problem/13974
const ll INF = 1e18;
int n, opt[5050][5050];
ll a[5050], DP[5050][5050], psum[5050];
int main() {
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            psum[i] = a[i] + psum[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            DP[i][i] = 0;
            opt[i][i] = i;
        }
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                ll mn = INF, mnk = -1;
                for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                    ll res = DP[i][k] + DP[k + 1][j] + (psum[j] - psum[i - 1]);
                    if (res < mn) {
                        mn = res;
                        mnk = k;
                    }
                }
                DP[i][j] = mn;
                opt[i][j] = mnk;
            }
        }
        cout << DP[1][n] << '\n';
    }
}

// Divide and Conquer Optimization 
// Recurrence: DP[t][i] = min(DP[t - 1][j] + C[j][i]) (1 <= j < n)
// Condition: Let opt[t][i] be j with the smallest value of DP[t - 1][j] + C[j][i]. It must satisfy opt[t][i] <= opt[t][i + 1].
// BOJ 12766 AC Code
// https://www.acmicpc.net/problem/12766
const ll INF = 1e18;
const int MAX = 5050;
int n, b, s, r;
ll w[MAX], dp[MAX][MAX], psum[MAX];
struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};
vector<wv> adj[MAX], radj[MAX];
void input() {
    cin >> n >> b >> s >> r;
    for (int i = 0; i < r; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({ d, v });
        radj[v].push_back({ d, u });
    }
}
vector<ll> dist(MAX, INF), rdist(MAX, INF);
void dijkstra() {
    priority_queue<wv> pq;
    pq.push({ 0, b + 1 });
    dist[b + 1] = 0;
    while (!pq.empty()) {
        int v = pq.top().v;
        ll w = pq.top().w;
        pq.pop();
        if (w > dist[v]) continue;
        for (auto& i : adj[v]) {
            if (dist[i.v] > w + i.w) {
                dist[i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
    pq.push({ 0, b + 1 });
    rdist[b + 1] = 0;
    while (!pq.empty()) {
        int v = pq.top().v;
        ll w = pq.top().w;
        pq.pop();
        if (w > rdist[v]) continue;
        for (auto& i : radj[v]) {
            if (rdist[i.v] > w + i.w) {
                rdist[i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
}
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        ll val = dp[gr - 1][i] + (mid - i - 1) * (psum[mid] - psum[i]);
        if (res > val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
    }
}
int main() {
    input();
    dijkstra();
    for (int i = 1; i <= b; i++) {
        w[i] = dist[i] + rdist[i];
    }
    sort(w + 1, w + 1 + b);
    for (int i = 1; i <= b; i++) {
        psum[i] = w[i] + psum[i - 1];
    }
    for (int i = 1; i <= b; i++) {
        dp[1][i] = (i - 1) * psum[i];
    }
    for (int i = 2; i <= s; i++) {
        f(i, i, b, 0, b);
    }
    cout << dp[s][b];
}