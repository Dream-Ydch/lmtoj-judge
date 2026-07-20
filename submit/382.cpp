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
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	writeln(read() + read());
	return 0;
}