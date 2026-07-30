// Hi-Star 8.2 / 9 Alpha
// From :
// ID :
// English Name :
// Chinese Name :

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define INF64 0x3f3f3f3f3f3f3f3f
#define INF32 0x3f3f3f3f
#define forab(a, b) for (ll i = a; i <= b; i++)
#define rofba(b, a) for (ll i = b; i >= a; i--)
#define forabj(a, b) for (ll j = a; j <= b; j++)
#define rofbaj(b, a) for (ll j = b; j >= a; j--)
using namespace std;

// Constants

// Structures

// Variables
ll dp[1009][1009];
pair<ll, ll> a[109];
ll t, m;

// Functions
void fastcin();
int return0();

// Main code
int main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  cin >> t >> m;
  for (int i = 1; i <= m; i++)
    cin >> a[i].first >> a[i].second;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= t; j++) {
      if (j >= a[i].first)
        dp[i][j] =
            max(dp[i - 1][j], dp[i - 1][j - a[i].first] + a[i].second);
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  cout << dp[m][t];
  return 0;
}

// Functions (code)

void fastcin() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
}

int return0() {
  exit(0);
  return 0;
}