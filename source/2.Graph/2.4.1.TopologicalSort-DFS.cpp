/////////////////////////////////////////////////////
// 3.4.1. Topological Sort - DFS                   //
/////////////////////////////////////////////////////
const int MAX = 101010;
int n, m;
vector<int> adj[MAX];
stack<int> stk;
int vi[MAX], fi[MAX], isCycle;
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
}
void dfs(int v) {
	vi[v] = 1;
	for (int next : adj[v]) {
		if (!vi[next]) dfs(next);
		else if (!fi[next]) isCycle = 1;
	}
	fi[v] = 1;
	stk.push(v);
}
void topologicalSort() {
	for (int i = 1; i <= n; i++) {
		if (!vi[i]) dfs(i);
	}
	if (isCycle) cout << 0;
	else {
		while (!stk.empty()) {
			cout << stk.top() << ' ';
			stk.pop();
		}
	}
}
int main() {
	input();
	topologicalSort();
}
/////////////////////////////////////////////////////
// 3.4.2. Topological Sort - Indegree              //
/////////////////////////////////////////////////////
const int MAX = 101010;
int n, m;
vector<int> adj[MAX], ts;
int ind[MAX], isCycle;
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		ind[v]++;
	}
}
void topologicalSort() {
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (ind[i] == 0) q.push(i);
	for (int i = 0; i < n; i++) {
		if (q.empty()) {
			isCycle = 1;
			break;
		}
		int v = q.front();
		q.pop();
		ts.push_back(v);
		for (int next : adj[v]) {
			ind[next]--;
			if (ind[next] == 0) q.push(next);
		}
	}
	if (isCycle) cout << 0;
	else {
		for (int i = 0; i < ts.size(); i++)
			cout << ts[i] << ' ';
	}
}
int main() {
	input();
	topologicalSort();
}