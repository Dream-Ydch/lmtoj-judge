/*--------------------------------------
  Hi-Star 9.1.236 (2026.3.29) (2026.7.25)
  From          :
  ID            :
  English Name  :
  Chinese Name  :
  Coding Time   :
  Difficulty    :
--------------------------------------*/

// htoj.com.cn |  luogu.com.cn  | xmoj.tech | atcoder.jp
//  etiger.vip | codeforces.com | hydro.ac  | vjudge.net

#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define ld long double
#define lll __int128
#define pll pair<ll, ll>
#define INF64 0x3f3f3f3f3f3f3f3f
#define INF32 0x3f3f3f3f
#define forab(a, b) for (ll i = a; i <= b; i++)
#define rofba(b, a) for (ll i = b; i >= a; i--)
#define forabj(a, b) for (ll j = a; j <= b; j++)
#define rofbaj(b, a) for (ll j = b; j >= a; j--)
#define endl '\n'
using namespace std;

// Constants

// Structures

// Variables
multiset<ll> st;

// Functions (code)
inline void fastcin() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

// Main code
int main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  fastcin();
  ll n;
  cin >> n;
  while (n--) {
    ll a;
    cin >> a;
    st.insert(a);
  }
  while (!st.empty()) {
    cout << *st.begin() << " ";
    st.erase(st.begin());
  }
  return 0;
}

// RP++ CSP-S 2026 300pts!