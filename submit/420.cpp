#include <bits/stdc++.h>
#define int long long
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
namespace gcd
{
	inline int _gcd(int x,int y) { return !y ? x : _gcd(y,x % y); }
	inline int gcd(int x,int y) { return x * y == 0 ? x + y : _gcd(x,y); }
}
namespace modint
{
	using ll = long long;
	inline ll power(ll a,ll b,ll p)
	{
		ll ans = 1; a %= p;
		while(b)
		{
			if(b & 1)	ans = ans * a % p;
			b >>= 1; a = a * a % p;
		}
		return ans;
	}
	template<ll mod>
	struct modint
	{
		ll x;
		modint() : x(0) { }
		modint(int n) : x(n) { }
		inline modint& operator ++ () { return *this += 1; }
		inline modint operator ++ (signed) { modint tmp = *this; *this += 1; return tmp; }
		inline modint& operator -- () { return *this -= 1; }
		inline modint operator -- (signed) { modint tmp = *this; *this -= 1; return tmp; }
		inline modint& operator = (ll y) { x = (y % mod + mod) % mod; return *this; }
		inline modint operator - () { return (mod - x) % mod; }
	};
	template<ll mod> inline modint<mod> operator + (modint<mod> x,modint<mod> y) { return {(x.x + y.x) % mod}; }
	template<ll mod> inline modint<mod> operator - (modint<mod> x,modint<mod> y) { return {(x.x - y.x + mod) % mod}; }
	template<ll mod> inline modint<mod> operator * (modint<mod> x,modint<mod> y) { return {x.x * y.x % mod}; }
	template<ll mod> inline modint<mod> operator / (modint<mod> x,modint<mod> y) { return {x.x * power(y.x,mod - 2,mod) % mod}; }
	template<ll mod> inline modint<mod> operator + (modint<mod> x,ll y) { return {(x.x + y % mod) % mod}; }
	template<ll mod> inline modint<mod> operator - (modint<mod> x,ll y) { return {(x.x - y % mod + mod) % mod}; }
	template<ll mod> inline modint<mod> operator * (modint<mod> x,ll y) { return {x.x * (y % mod) % mod}; }
	template<ll mod> inline modint<mod> operator / (modint<mod> x,ll y) { return {x.x * power(y % mod,mod - 2,mod) % mod}; }
	template<ll mod> inline modint<mod>& operator += (modint<mod> &x,modint<mod> y) { return x = x + y; }
	template<ll mod> inline modint<mod>& operator -= (modint<mod> &x,modint<mod> y) { return x = x - y; }
	template<ll mod> inline modint<mod>& operator *= (modint<mod> &x,modint<mod> y) { return x = x * y; }
	template<ll mod> inline modint<mod>& operator /= (modint<mod> &x,modint<mod> y) { return x = x / y; }
	template<ll mod> inline modint<mod>& operator += (modint<mod> &x,ll y) { return x = x + y; }
	template<ll mod> inline modint<mod>& operator -= (modint<mod> &x,ll y) { return x = x - y; }
	template<ll mod> inline modint<mod>& operator *= (modint<mod> &x,ll y) { return x = x * y; }
	template<ll mod> inline modint<mod>& operator /= (modint<mod> &x,ll y) { return x = x / y; }
	template<ll mod> inline ostream& operator << (ostream& out,modint<mod> x) { return out << x.x; }
	template<ll mod> inline istream& operator >> (istream& in,modint<mod> x) { in >> x.x; x.x %= mod; (x.x += mod) %= mod; return in; }
	template<ll mod> inline bool operator == (modint<mod> x,modint<mod> y) { return x.x == y.x; }
	template<ll mod> inline bool operator < (modint<mod> x,modint<mod> y) { return x.x < y.x; }
	template<ll mod> inline bool operator <= (modint<mod> x,modint<mod> y) { return x.x <= y.x; }
	template<ll mod> inline bool operator > (modint<mod> x,modint<mod> y) { return x.x > y.x; }
	template<ll mod> inline bool operator >= (modint<mod> x,modint<mod> y) { return x.x >= y.x; }
	template<ll mod> inline bool operator == (modint<mod> x,int y) { return x.x == y; }
	template<ll mod> inline bool operator < (modint<mod> x,int y) { return x.x < y; }
	template<ll mod> inline bool operator <= (modint<mod> x,int y) { return x.x <= y; }
	template<ll mod> inline bool operator > (modint<mod> x,int y) { return x.x > y; }
	template<ll mod> inline bool operator >= (modint<mod> x,int y) { return x.x >= y; }
	template<ll mod> inline bool operator == (int x,modint<mod> y) { return x == y.x; }
	template<ll mod> inline bool operator < (int x,modint<mod> y) { return x < y.x; }
	template<ll mod> inline bool operator <= (int x,modint<mod> y) { return x <= y.x; }
	template<ll mod> inline bool operator > (int x,modint<mod> y) { return x > y.x; }
	template<ll mod> inline bool operator >= (int x,modint<mod> y) { return x >= y.x; }
	template<ll mod> inline void write(modint<mod> x) { ::write(x.x); }
	template<ll mod> inline void writeln(modint<mod> x) { ::writeln(x.x); }
}
// #define DEBUG
namespace debug
{
#ifdef DEBUG
	template<typename... Args> inline void write(Args... args) { int tmp[] = {(cout << args,0)... }; }
	template<typename T> inline void print(T *a,int l,int r) { for(int i = l;i <= r;i++) write(a[i],' '); write('\n'); }
#else
	template<typename... Args> inline void write(Args... args) { }
	template<typename T> inline void print(T *a,int l,int r) { }
#endif
}
namespace mysort
{
	template<typename T,typename f> inline void merge(T *a,int l,int r,f cmp = less<T>())
	{
		if(l == r)	return;
		if(l > r)	return;
		int mid = l + r >> 1;
		merge(a,l,mid,cmp); merge(a,mid + 1,r,cmp);
		int pos1 = l,pos2 = mid + 1;
		vector<T> tmp;
		while(pos1 != mid + 1 || pos2 != r + 1)
			if(pos1 == mid + 1)	tmp.push_back(a[pos2++]);
			else if(pos2 == r + 1)	tmp.push_back(a[pos1++]);
			else if(cmp(a[pos1],a[pos2]))	tmp.push_back(a[pos1++]);
			else	tmp.push_back(a[pos2++]);
		int cnt = 0;
		for(int i = l;i <= r;i++)	a[i] = tmp[cnt++];
	}
}
inline int max(int a,int b) { return a > b ? a : b; }
inline int min(int a,int b) { return a < b ? a : b; }
const int inf = 1e18;
const int N = 3;
int n,aa[N];
struct line
{
	int a,b;
	inline friend line operator + (line a1,line b1) { return {a1.a + b1.a,a1.b + b1.b}; }
};
inline void swap(line &a,line &b)
{
	line t; t.a = a.a; t.b = a.b;
	a.a = b.a; a.b = b.b;
	b.a = t.a; b.b = t.b;
}
inline pair<line,int> maxx(line a,line b)
{
	if(a.a < b.a || (a.a == b.a && a.b < b.b))	swap(a,b);
	if(a.b >= b.b)	return {a,inf};
	return {b,(b.b - a.b) / (a.a - b.a)};
}
struct node
{
	line lmax,rmax,maxn,sum;
	int intr;
	inline void init() { lmax = rmax = maxn = sum = {0,0}; intr = inf; }
	inline friend node operator + (node a,node b)
	{
		node c;
		pair<line,int> tmp;
		c.intr = min(a.intr,b.intr);
		tmp = maxx(a.lmax,a.sum + b.lmax);
		c.lmax = tmp.first;
		c.intr = min(c.intr,tmp.second);
		tmp = maxx(b.rmax,b.sum + a.rmax);
		c.rmax = tmp.first;
		c.intr = min(c.intr,tmp.second);
		tmp = maxx(a.maxn,b.maxn);
		c.intr = min(c.intr,tmp.second);
		tmp = maxx(a.rmax + b.lmax,tmp.first);
		c.maxn = tmp.first;
		c.intr = min(c.intr,tmp.second);
		c.sum = a.sum + b.sum;
		return c;
	}
};
struct KTT
{
	node tr[N << 2];
	int lazy[N << 2];
	inline void up(int id) { tr[id] = tr[id << 1] + tr[id << 1 | 1]; }
	inline void push(int id,int val)
	{
		lazy[id] += val;
		tr[id].intr -= val;
		tr[id].lmax.b += tr[id].lmax.a * val;
		tr[id].rmax.b += tr[id].rmax.a * val;
		tr[id].maxn.b += tr[id].maxn.a * val;
		tr[id].sum.b += tr[id].sum.a * val;
	}
	inline void down(int id)
	{
		if(!lazy[id])	return;
		push(id << 1,lazy[id]);
		push(id << 1 | 1,lazy[id]);
		lazy[id] = 0;
	}
	inline void build(int id,int l,int r)
	{
		lazy[id] = 0;
		if(l == r)
		{
			tr[id].lmax = tr[id].rmax = tr[id].maxn = tr[id].sum = {1,aa[l]};
			tr[id].intr = inf;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1,l,mid);
		build(id << 1 | 1,mid + 1,r);
		up(id);
	}
	inline void rebuild(int id)
	{
		if(tr[id].intr >= 0)	return;
		down(id);
		rebuild(id << 1);
		rebuild(id << 1 | 1);
		up(id);
	}
	inline void add(int id,int l,int r,int ql,int qr,int val)
	{
		if(l >= ql && r <= qr) { push(id,val); rebuild(id); return; }
		down(id);
		int mid = (l + r) >> 1;
		if(ql <= mid)	add(id << 1,l,mid,ql,qr,val);
		if(qr > mid)	add(id << 1 | 1,mid + 1,r,ql,qr,val);
		up(id);
	}
	inline node query(int id,int l,int r,int ql,int qr)
	{
		if(l >= ql && r <= qr)	return tr[id];
		down(id);
		int mid = (l + r) >> 1;
		node ans;
		ans.init();
		if(ql <= mid)	ans = ans + query(id << 1,l,mid,ql,qr);
		if(qr > mid)	ans = ans + query(id << 1 | 1,mid + 1,r,ql,qr);
		return ans;
	}
} tr;
int add = 2e9;
signed main()
{
	n = 2; tr.build(1,1,n);
	tr.add(1,1,n,1,1,read() + add); tr.add(1,1,n,2,2,read() + add);
	if(aa[1] >= 0 && aa[2] >= 0)	writeln(tr.query(1,1,n,1,2).maxn.b - 2 * add);
	else	writeln(tr.query(1,1,n,1,1).maxn.b + tr.query(1,1,n,2,2).maxn.b - 2 * add);
	return 0;
}