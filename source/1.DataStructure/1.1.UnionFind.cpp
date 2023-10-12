const int MAX = 1010101;
int n;
vector<int> uf(MAX, -1);
int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
}
int main() {
	cin >> n;
	int q; cin >> q;
	while (q--) {
		int op, u, v;
		cin >> op >> u >> v;
		if (op == 0) merge(u, v);
		if (op == 1) {
			if (find(u) == find(v)) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}