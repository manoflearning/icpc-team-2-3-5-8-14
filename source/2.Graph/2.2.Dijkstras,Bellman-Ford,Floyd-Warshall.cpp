// Bellman-Ford Algorithm
const int MAX = 101010;
const ll INF = 1e18;
struct wv {
	ll w; int v;
};
int n, m;
vector<wv> adj[MAX];
vector<ll> upper(MAX, INF);
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
}
int bellmanFord() {
	upper[1] = 0;
	int update = 1;
	for (int i = 0; i <= n; i++) {
		update = 0;
		for (int now = 1; now <= n; now++) {
			if (upper[now] == INF) continue;
			for (wv e : adj[now]) {
				int next = e.v;
				if (upper[next] > upper[now] + e.w) {
					upper[next] = upper[now] + e.w;
					update = 1;
				}
			}
		}
		if (!update) break;
	}
	return !update;
}
int main() {
	input();
	if (bellmanFord()) {
		for (int i = 2; i <= n; i++) {
			if (upper[i] == INF) cout << -1 << '\n';
			else cout << upper[i] << '\n';
		}
	}
	else cout << -1 << '\n';
}
// Floyd-Warshall Algorithm
const ll INF = 1e18;
const int MAXV = 101;
int n, m;
ll adj[MAXV][MAXV];
void init() {
	for (int i = 0; i < MAXV; i++) {
		for (int j = 0; j < MAXV; j++) {
			adj[i][j] = INF;
		}
	}
}
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; ll w;
		cin >> u >> v >> w;
		adj[u][v] = min(adj[u][v], w);
	}
}
void floyd() {
	for (int i = 1; i <= n; i++) adj[i][i] = 0;
	for (int k = 1; k <= n; k++) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}
int main() {
	init();
	input();
	floyd();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (adj[i][j] == INF) cout << 0 << ' ';
			else cout << adj[i][j] << ' ';
		}
		cout << '\n';
	}
}