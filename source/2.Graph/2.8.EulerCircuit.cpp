// Hierholzer's Algorithm
const int MAXV = 1010;
int n, adj[MAXV][MAXV], nxt[MAXV];
vector<int> eulerCircult;
void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> adj[i][j];
		}
	}
}
int doesEulerCircuitExist() {
	// If the degree of all nodes in the graph is even, then an euler circuit exists.
	// Otherwise, the euler circuit does not exist.
	// We can do similar way to determine the existence of euler path. 
	// If only two vertices have odd degree, than an eular path exists. Otherwise, the euler path does not exist.
	for (int i = 1; i <= n; i++) {
		int deg = 0;
		for (int j = 1; j <= n; j++) {
			deg += adj[i][j];
		}
		if (deg & 1) return 0;
	}
	return 1;
}
void dfs(int now) {
	for (int& x = nxt[now]; x <= n; x++) {
		while (x <= n && adj[now][x]) {
			adj[now][x]--;
			adj[x][now]--;
			dfs(x);
		}
	}
	eulerCircult.push_back(now);
}
int main() {
	input();
	if (!doesEulerCircuitExist()) {
		cout << "Euler Circuit does not exist";
		return 0;
	}
	for (int i = 1; i <= n; i++) nxt[i] = 1;
	dfs(1);
	for (auto i : eulerCircult) 
		cout << i << ' ';
}