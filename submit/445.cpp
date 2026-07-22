#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, ll> mapsort;
int main() {
  ll n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    ll a;
    cin >> a;
    mapsort[a]++;
  }
  for (map<ll, ll>::iterator it = mapsort.begin(); it != mapsort.end(); it++) {
    for (int i = 1; i <= it->second; i++) {
      cout << it->first << " ";
    }
  }
  return 0;
}