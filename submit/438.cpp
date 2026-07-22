#include<bits/stdc++.h>
using namespace std;
int w[105];
int v[105];
int dp[1005];
int main(){
    int T,M;
    cin>>T>>M;
    for(int i=1;i<=M;i++){
        cin>>w[i]>>v[i];
    }
    for(int i=1;i<=M;i++){
        for(int j=T;j>=w[i];j--){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[T]<<endl;
    return 0;
}