#include<bits/stdc++.h>
using namespace std;
string s1, s2;
int a[510], b[510], c[510];
int main(){
	cin >> s1 >> s2;
	reverse(s1.begin(), s1.end()), reverse(s2.begin(), s2.end());
	for (int i = 0; i < s1.size(); i++) a[i] = s1[i] - '0';
	for (int i = 0; i < s2.size(); i++) b[i] = s2[i] - '0';
	int l = max(s1.size(), s2.size());
	for (int i = 0; i < l; i++)
	{
		c[i] += (a[i] + b[i]);
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	if (c[l] == 0) l--;
	for (int i = l; i >= 0; i--) cout << c[i];
    return 0;
}