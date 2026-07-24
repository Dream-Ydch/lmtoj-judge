#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
inline int read()
{
	int x = 0,p = 1;
	char c = getchar();
	while(c > '9' || c < '0')	p = c == '-' ? -1 : 1,c = getchar();
	while(c >= '0' && c <= '9')	x = (x << 1) + (x << 3) + (c ^ 48),c = getchar();
	return p * x;
}
inline void write(char x) { putchar(x); }
inline void write(const char* s) { int len = strlen(s); for(int i = 0;i < len;i++) putchar(s[i]); }
template<typename _Tp> inline void _write(_Tp x) { if(x > 9) _write(x / 10); putchar(x % 10 | 48); }
template<typename _Tp> inline void write(_Tp x) { if(x < 0) putchar('-'),x = -x; _write(x); }
template<typename _Tp> inline void writeln(_Tp x) { write(x); puts(""); }
template<typename... Args> inline void write(Args... args) { int tmp[] = {(write(args),0)... }; }
template<typename... Args> inline void writeln(Args... args) { int tmp[] = {(write(args),0)... }; puts(""); }
const int inf = 1e9;
const int N = 1e7 + 10;
int n,m,seed;
struct random
{
	int x = 0,seed;
	random() { }
	inline void init(int s) { seed = s; }
	inline int getrand() { x ^= (x >> 15) | (x << 17); x ^= (x >> 11); x ^= (x << 7) | seed; x = (x & 0xffffff00) | ((x ^ (x >> 8)) & 0xffffff); x ^= (x << 15) & seed; x ^= (x << 18); return x; }
} rnd;
#define ll long long
unordered_map<int,int> mp;
int p[N << 1],sz[N << 1],tot = 0;
inline bool check(int x) { return mp.count(x); }
inline void build(int x) { mp[x] = ++tot; x = tot; p[x] = x; sz[x] = 1; }
inline int _find(int x) { return x == p[x] ? x : p[x] = _find(p[x]); }
inline int find(int x) { if(!check(x)) build(x); x = mp[x]; return _find(x); }
inline void swap(int &x,int &y) { int t = x; x = y; y = t; }
inline void unite(int x,int y)
{
	int fx = find(x),fy = find(y);
	if(fx == fy)	return;
	if(sz[fy] < sz[fx])	swap(fx,fy);
	p[fx] = fy; sz[fy] += sz[fx];
}
inline void getedge(int &u,int &v) { u = (rnd.getrand() % n + n) % n + 1; v = (rnd.getrand() % n + n) % n + 1; }
signed main()
{
	n = read(); m = read(); seed = read(); rnd.init(seed);
	mp.reserve(m << 1); mp.max_load_factor(0.8f);
	for(int i = 1,u,v;i <= m;i++)	getedge(u,v),unite(u,v);
	ll ans = 0; int id;
	for(int i = 1;i <= tot;i++)
		if(_find(i) == i)	ans += 1ll * sz[i] * (sz[i] - 1) / 2;
	writeln(ans);
	return 0;
}