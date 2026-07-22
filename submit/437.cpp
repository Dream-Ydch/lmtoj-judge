#include<bits/stdc++.h>
using namespace std;
int w[1000009];
int v[1000009];
int dp[1000009];
int main(){
	int n,W;
	cin>>W>>n;
	for(int i=1;i<=n;++i)cin>>w[i]>>v[i];
	for(int i=1;i<=n;++i){
		for(int j=W;j>=w[i];--j){
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		}
	}
	cout<<dp[W];
	return 0;
}