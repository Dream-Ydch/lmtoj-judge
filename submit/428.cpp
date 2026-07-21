#include <bits/stdc++.h>
#define int long long
#define fs(i,x,y) for(int i=(x);i<=(y);i++)
#define fj(i,x,y) for(int i=(x);i>=(y);i--)
using namespace std;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,m;
    cin >> t >> m;
    int f[1005] = {},a[1005] = {},b[1005] = {};
    for (int i = 1;i <= m;i ++){
        cin >> a[i] >> b[i];
    }
    for (int i = 1;i <= m;i ++){
        for (int j = t;j >= a[i];j --){
            f[j] = max(f[j],f[j-a[i]] + b[i]);
        }
    }
    cout << f[t];
    return 0;
}