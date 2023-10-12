/////////////////////////////////////////////////////
// 2.3.1 Segment Tree                              //
/////////////////////////////////////////////////////
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		for (int i = flag; i < flag + n; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;
int main() {
	int n, m, k; 
	cin >> n >> m >> k;
	seg.build(n);
	for (int i = 0; i < m + k; i++) {
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1) seg.modify(x, y);
		if (op == 2) cout << seg.query(x, y) << '\n';
	}
}
/////////////////////////////////////////////////////
// 2.3.2 Iterative Segment Tree                    //
/////////////////////////////////////////////////////
struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
		for (int i = 0; i < n; i++) cin >> t[n + i];
		for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;
int main() {
	int n, m, k;
	cin >> n >> m >> k;
	seg.build(n);
	for (int i = 0; i < m + k; i++) {
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1) seg.modify(x - 1, y);
		if (op == 2) cout << seg.query(x - 1, y) << '\n';
	}
}
/////////////////////////////////////////////////////
// 2.3.3. Segment Tree with Lazy Propagation       //
/////////////////////////////////////////////////////
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
		for (int i = flag; i < flag + n; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nr - nl + 1);
			lazy[n] = 0;
		}
	}
}seg;
int main() {
	int n, m, k;
	cin >> n >> m >> k;
	seg.build(n);
	for (int i = 0; i < m + k; i++) {
		ll op, x, y, z;
		cin >> op >> x >> y;
		if (op == 1) {
			cin >> z;
			seg.modify(x, y, z);
		}
		if (op == 2) cout << seg.query(x, y) << '\n';
	}
}
/////////////////////////////////////////////////////
// 2.3.4. Dynamic Segment Tree                     //
/////////////////////////////////////////////////////
#define sz(x) (int)(x).size()
const int MAXL = 1, MAXR = 1000000;
struct Node {
    ll x; int l, r;
};
struct Dyseg {
    vector<Node> t = { { 0, -1, -1 }, { 0, -1, -1 } };
    void modify(int p, ll x, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (p < nl || nr < p) return;
        t[n].x += x;
        if (nl < nr) {
            int mid = (nl + nr) >> 1;
            if (p <= mid) {
                if (t[n].l == -1) {
                    t[n].l = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].l, nl, mid);
            }
            else {
                if (t[n].r == -1) {
                    t[n].r = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].r, mid + 1, nr);
            }
        }
    }
    ll query(int l, int r, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].x;
        int mid = (nl + nr) >> 1;
        ll ret = 0;
        if (l <= mid) {
            if (t[n].l == -1) {
                t[n].l = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].l, nl, mid);
        }
        if (mid + 1 <= r) {
            if (t[n].r == -1) {
                t[n].r = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].r, mid + 1, nr);
        }
        return ret;
    }
}dyseg;
ll a[1010101];
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dyseg.modify(i, a[i]);
    }
    for (int i = 0; i < m + k; i++) {
        int op; ll x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            dyseg.modify(x, y - a[x]);
            a[x] = y;
        }
        if (op == 2) cout << dyseg.query(x, y) << '\n';
    }
}