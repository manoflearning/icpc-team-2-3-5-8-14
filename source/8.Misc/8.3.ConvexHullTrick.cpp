// BOJ 13263 AC Code
// https://www.acmicpc.net/problem/13263
struct lf { // f(x) = px + q, x >= s
    ll p, q; 
    double s;
    lf(): lf(1, 0) {}
    lf(ll sp, ll sq): p(sp), q(sq), s(0) {}
};
double cross(const lf& u, const lf& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}
int n;
ll a[101010], b[101010];
ll dp[101010];
lf ch[101010];
void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}
void convexHullTrick() {
    int top = 1;
    for (int i = 2; i <= n; i++) {
        lf g(b[i - 1], dp[i - 1]);
        while (top > 1) {
            g.s = cross(ch[top - 1], g);
            if (ch[top - 1].s < g.s) break;
            --top;
        }
        ch[top++] = g;
        int l = 1, r = top - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[i] < ch[mid].s) r = mid - 1;
            else l = mid;
        }
        int fpos = l;
        dp[i] = ch[fpos].p * a[i] + ch[fpos].q;
    }
}
int main() {
    input();
    convexHullTrick();
    cout << dp[n];
}