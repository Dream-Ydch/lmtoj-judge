#include<bits/stdc++.h>
#define int long long
//#define ull unsigned long long
using namespace std;
inline int read() {
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') {f = -1;}ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
void solve() {
    int a = read(), b = read();
cout << a + b;
}
signed main() {
	solve();
	return 0;
}