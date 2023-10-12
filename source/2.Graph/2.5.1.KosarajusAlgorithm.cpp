/////////////////////////////////////////////////////
// 3.5.1. Kosaraju's Algorithm                     //
/////////////////////////////////////////////////////
#define sz(x) (int)(x).size()
const int MAXV = 10101;
int n, m;
vector<int> adj[MAXV], radj[MAXV];
int in[MAXV], out[MAXV], num, p[2 * MAXV];
int vi[MAXV], cnt;
vector<vector<int>> scc;
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		radj[v].push_back(u);
	}
}
void dfs(int v) {
	in[v] = ++num;
	for (auto& i : radj[v]) {
		if (!in[i]) dfs(i);
	}
	out[v] = ++num;
	p[num] = v;
}
void flood(int v) {
	scc[cnt].push_back(v);
	vi[v] = cnt;
	for (auto& i : adj[v]) {
		if (!vi[i]) flood(i);
	}
}
void kosaraju() {
	for (int v = 1; v <= n; v++) {
		if (!in[v]) dfs(v);
	}
	for (int v = 2 * n; v >= 1; v--) {
		if (!p[v]) continue;
		if (vi[p[v]]) continue;
		cnt++;
		scc.resize(cnt + 1);
		flood(p[v]);
	}
}
void print() {
	for (auto& i : scc)
		sort(i.begin(), i.end());
	sort(scc.begin(), scc.end());
	cout << sz(scc) - 1 << '\n';
	for (int i = 1; i < sz(scc); i++) {
		auto& arr = scc[i];
		for (auto& j : arr) cout << j << ' ';
		cout << -1 << '\n';
	}
}
int main() {
	input();
	kosaraju();
	print();
}
/////////////////////////////////////////////////////
// 3.5.2. Tarjan's Algorithm                       //
/////////////////////////////////////////////////////
const int MAXV = 101010;
int n, m, label[MAXV], labelCnt;
int SCCnum[MAXV], SCCcnt, finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
vector<vector<int>> SCC;
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
}
int dfs(int v) {
	label[v] = labelCnt++;
	stk.push(v);
	int ret = label[v];
	for (int next : adj[v]) {
		// Unvisited node.
		if (label[next] == -1) ret = min(ret, dfs(next));
		// Visited but not yet classified as SCC. In other words, edge { v, next } is back edge.
		else if (!finished[next]) ret = min(ret, label[next]);
	}
	// If there is no edge to the ancestor node among itself and its descendants, find scc.
	if (ret == label[v]) {
		vector<int> vSCC;
		while (1) {
			int t = stk.top();
			stk.pop();
			vSCC.push_back(t);
			SCCnum[t] = SCCcnt;
			finished[t] = 1;
			if (t == v) break;
		}
		SCC.push_back(vSCC);
		SCCcnt++;
	}
	return ret;
}
void getSCC() {
	memset(label, -1, sizeof(label));
	for (int v = 1; v <= n; v++)
		if (label[v] == -1) dfs(v);
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);	
	input();
	getSCC();
	return 0;
}