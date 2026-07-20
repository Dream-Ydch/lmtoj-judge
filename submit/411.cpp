#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	vector<int>a;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	sort(a.begin,a.end();
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}