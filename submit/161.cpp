#include <bits/stdc++.h>
using namespace std;

string s,t;
int c[110];
int a[110];
int b[110];
int cnt1=1,cnt2=1;

int main(){
	cin >> s >> t;
	
	int la = s.size();
	int lb = t.size();
	
	if(la < lb){
		swap(la,lb);
		string temp = s;
		s = t;
		t = temp;
	}
	
	for(int i = 0;i < la;i++) a[la - i] = s[i] - 48;
	for(int i = 0;i < lb;i++) b[lb - i] = t[i] - 48;
	
	int r = 0;
	for(int i = 1;i <= la + 1;i++){
		c[i] = (a[i] + b[i] + r) % 10;
		r = (a[i] + b[i] + r) / 10;
	}
	
	if(c[la + 1]) cout << c[la + 1];
	for(int i = la;i >= 1;i--) cout << c[i];
	return 0;
}