/*--------------------------------------
  Hi-Star 9.1.234 (2026.3.29) (2026.7.7)
  From          :
  ID            :
  English Name  :
  Chinese Name  :
  Coding Time   :
  Difficulty    :
--------------------------------------*/

// htoj.com.cn |  luogu.com.cn  | xmoj.tech | atcoder.jp
//  etiger.vip | codeforces.com | hydro.ac  | vjudge.net

#include <bits/extc++.h>
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define ld long double
#define lll __int128
#define pll pair<ll, ll>
#define INF64 0x3f3f3f3f3f3f3f3f
#define INF32 0x3f3f3f3f
#define INF16 0x3f3f
#define INF8 0x3f
#define forab(a, b) for (ll i = a; i <= b; i++)
#define rofba(b, a) for (ll i = b; i >= a; i--)
#define forabj(a, b) for (ll j = a; j <= b; j++)
#define rofbaj(b, a) for (ll j = b; j >= a; j--)
#define endl '\n'
using namespace std;

// Constants
const ld pie = acos(-1.0);

// Structures

// Variables
ll n;
ll a[666666];

// Functions (code)
inline void fastcin() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}
inline ll lowbit(ll x) { return x & -x; };

// Main code
int main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  fastcin();
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    cout << a[i] << " ";
  }
  return 0;
}