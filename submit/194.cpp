#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
using namespace std;

bool beginmem;
constexpr int N = 2000010;
constexpr int mod = 998244353;
constexpr int i2 = mod + 1 >> 1;
constexpr int inf = 1e18;
using ld = long double;
using u32 = unsigned;
using u64 = unsigned long long;
using i128 = __int128;

inline int power(int a, int b, int c) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = sum * a % c;
        a = a * a % c, b >>= 1;
    }
    return sum;
}

inline int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int xp, yp, g = exgcd(b, a % b, xp, yp);
    return x = yp, y = xp - a / b * yp, g;
}

inline int inversion(int a, int Mod = mod) { return power(a, Mod - 2, Mod); }

inline u64 splitmix64(u64 x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

// 月が綺麗ねと言われたい

namespace lowspeed_song {

inline void init() {
}

int a[N], b[N], c[N], pre[N], suf[N], res[N];

struct DSU {
    int fa[N];
    inline DSU() { iota(fa, fa + N, 0); }
    inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    inline int merge(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) return fa[x] = y, 1;
        return 0;
    }
} dsu;

pair<int, int> ls[N];
vector<pair<int, int>> Q[N];
int top, now, n, q, ll[N], rr[N], w[N], L[N], R[N], vis[N];

inline void push(int val) {
    now += val;
    if (top && ls[top - 1].first == val) ++ls[top - 1].second;
    else ls[top++] = {val, 1};
    while (top > 2) {
        if (ls[top - 2].second != 1 || ls[top - 2].first >= ls[top - 1].first || ls[top - 2].first >= ls[top - 3].first) break;
        now += max(ls[top - 1].first, ls[top - 3].first) - ls[top - 2].first;
        if (ls[top - 1].first >= ls[top - 3].first) {
            int mv = ls[top - 1].first, ml = ls[top - 1].second + 1;
            top -= 2;
            if (top && ls[top - 1].first == mv) ml += ls[--top].second;
            ls[top++] = {mv, ml};
        } else {
            int mv = ls[top - 1].first, ml = ls[top - 1].second;
            top -= 2, ++ls[top - 1].second, ls[top++] = {mv, ml};
        }
    }
}

inline void dfs(int u) {
    dsu.fa[u] = u;
    if (L[u]) dfs(L[u]), dsu.fa[dsu.find(L[u])] = u;
    if (R[u]) dfs(R[u]), dsu.fa[dsu.find(R[u])] = u;
    vis[u] = 1;
    for (auto &[v, id] : Q[u]) if (vis[v]) {
        int pos = dsu.find(v), l = min(u, v), r = max(u, v);
        res[id] = a[l] + a[r] - a[pos] + rr[l] - rr[pos] + ll[r] - ll[pos];
    }
}

inline void sol() {
    int a, b; cin >> a >> b;
    cout << a + b << '\n';
    
}

} // namespace lowspeed_song

bool endmem;

signed main() {
    srand(time(0));
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(5);
    // int c; cin >> c;
    int T = 1;
    // cin >> T;
    lowspeed_song::init();
    for (int ca = 1; ca <= T; ++ca) lowspeed_song::sol();
    cerr << "Memory Used " << abs(&beginmem - &endmem) / 1048576. << " MB.\n";
    return 0;
}