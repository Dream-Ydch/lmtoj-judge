// Author: heffo_hard
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)=-~(a))
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)=~-(a))
#define fst first
#define sed second
#define pref static inline
#define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++
using namespace std;
using hint = __int128;
using pii = pair<int, int>;
using us = unsigned short;
using ldb = long double;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using vpil = vector<pil>;
using vl = vector<ll>;
using pli = pair<ll, int>;
using vpli = vector<pli>;
using vi = vector<int>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using db = double;
ull n,k;
namespace mystl {
    char buf[1 << 20],*p1 = buf,*p2 = buf, sr[1 << 23], z[23], nc;
    int C =-1, Z = 0;
    template<typename T>pref void read(T & x){
        bool flag = false;
        while (nc = gc(), (nc<48 || nc> 57) && nc !=-1) flag |= (nc == 45); 
        x = nc - 48;
        while (nc = gc(), 47 < nc && nc < 58) x = (x << 3) + (x << 1) + (nc ^ 48); 
        if (flag) x = -x;
    }
    pref void read(char* s) {
        char ch = gc();
        while(ch <= 32) ch = gc();
        int i = 0;
        while(ch > 32) {
            s[i++] = ch;
            ch = gc();
        }
        s[i] = '\0';
    }
    pref void read(string &s) {
        s.clear();
        char ch = gc();
        while(ch <= 32) ch = gc();
        while(ch > 32) {
            s += ch;
            ch = gc();
        }
    }
    pref void read(char &ch) {
        ch = gc();
        while(ch <= 32) ch = gc();
    }
    
    template<typename T, typename ... Args_Arrays_Typename_heffo_hard>
    void read(T & x, Args_Arrays_Typename_heffo_hard & ...a){read(x); read(a...);}
    
    pref void ot(){fwrite(sr, 1, C + 1, stdout ); C = -1;}
    pref void flush(){if (C > 1 << 22) ot();} 
    template<typename T>pref void write(T x) {
        if constexpr (is_same<T, char>::value) {
            sr[++C] = x;
        } else if constexpr (is_same<T, const char*>::value || is_same<T, char*>::value) {
            for(int i = 0; x[i]; ++i) sr[++C] = x[i];
        } else if constexpr (is_same<T, string>::value) {
            for(char c : x) sr[++C] = c;
        } else {
            int y = 0;
            if (x < 0) y = 1, x = -x;
            Z = 0;
            do {
                z[++Z] = x % 10 + 48;
                x /= 10;
            } while (x);
            if (y) z[++Z] = '-';
            while (Z) sr[++C] = z[Z--];
        }
        flush();
    }
    
    template<typename T>pref void write(T x, char t) {
        write(x);
        sr[++C] = t;
        flush();
    }
    
    pref void write(const char* s) {
        for(int i = 0; s[i]; ++i) sr[++C] = s[i];
        flush();
    }
    
    pref void write(string s) {
        for(char c : s) sr[++C] = c;
        flush();
    }
    
    pref ll qpow(ll a, ll b, ll p){
        if (a == 0) return 0;
        ll c = 1ll;
        while (b){
            if (b & 1) c = a * c % p; 
            a = a * a % p; 
            b >>= 1;
        } 
        return c;
    }
    
    pref ll lcm(ll x, ll y){
        return x / std:: __gcd(x, y) * y;
    }
};
using namespace mystl;
namespace my {
    constexpr int P = static_cast<int>(998244353);
    pref void madd(int & x, int y){x = (x + y >= P) ? (x + y - P) : (x + y);}
    pref int fmadd(int x, int y){return (x + y >= P) ? (x + y - P) : (x + y);}
    pref void msub(int & x, int y){x = (x < y) ? (x - y + P) : (x - y);}
    pref int fmsub(int x, int y){return (x < y) ? (x - y + P) : (x - y);}
    pref void mmul(int & x, int y){x = (int)(1ll * x * y % P);}
    pref int fmmul(int x, int y){return (int)(1ll * x * y % P);}
    
    template<typename T>pref T min(T x, T y){return (x < y) ? (x) : (y);}
    template<typename T>pref T max(T x, T y){return (x > y) ? (x) : (y);}
    template<typename T>pref T abs(T x){return (x < 0) ? (-x) : (x);}
    
    constexpr int N = static_cast<int>(0), inf = static_cast<int>(0x3f3f3f3f3f);

    pref void solve(){
        k^=k>>1;
        while(~--n)write(k>>n&1);
    }
}
int main(){
    //  freopen("","r",stdin);
    //  freopen("","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    read(n,k);
    my::solve();
    ot();
    return 0;
}
/*

*/