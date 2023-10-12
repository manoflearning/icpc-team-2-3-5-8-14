#define pii pair<int, int>
#define fr first
#define sc second
const int MAXV = 20202;
int n, m;
int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
pii p[MAXV];
int ans[MAXV / 2];
inline int inv(int x) {
	// negative number -a indicates ¬a.
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}
void twoCnf(int a, int b) {
	// (a ∨ b) iff (¬a → b) iff (¬b → a)
	adj[inv(-a)].push_back(inv(b));
	adj[inv(-b)].push_back(inv(a));
}
void buildGraph() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		twoCnf(a, b);
	}
}
int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;
	stk.push(now);
	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}
	if (ret >= dfsn[now]) {
		while (1) {
			int t = stk.top();
			stk.pop();
			sNum[t] = sCnt;
			finished[t] = 1;
			if (t == now) break;
		}
		sCnt++;
	}
	return ret;
}
int isSatisfiable() {
	// determining satisfiability 
	int isS = 1;
	for (int v = 0; v < 2 * n; v += 2) {
		// if x and ¬x is in same scc, then the proposition is not satisfiable
		if (sNum[v] == sNum[v + 1]) {
			isS = 0;
			break;
		}
	}
	return isS;
}
void findValueOfEachVariable() {
	// order of scc is the reverse of the topological sort
	for (int v = 0; v < 2 * n; v++) {
		p[v] = { sNum[v], v };
	}
	sort(p, p + 2 * n);
	// determining true/false of each variable
	for (int i = 2 * n - 1; i >= 0; i--) {
		int v = p[i].sc;
		if (ans[v / 2 + 1] == -1) 
			ans[v / 2 + 1] = (v & 1) ? 1 : 0;
	}
	for (int v = 1; v <= n; v++)
		cout << ans[v] << ' ';
}
int main() {
	memset(dfsn, -1, sizeof(dfsn));
	memset(ans, -1, sizeof(ans));
	buildGraph();
	// finding scc
	for (int v = 0; v < 2 * n; v++)
		if (dfsn[v] == -1) dfs(v);
	if (isSatisfiable()) {
		cout << 1 << '\n';
		findValueOfEachVariable();
	}
	else cout << 0;
}