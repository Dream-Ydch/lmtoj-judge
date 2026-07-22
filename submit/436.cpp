#include<bits/stdc++.h>
using namespace std;
int W,n,w[1009],v[1009],dp[1009]={0};
int mo[1009][1009]={0};
int dfs(int i,int j){
    if(mo[i][j]!=-1)return mo[i][j];
    if(i>n){return mo[i][j]=0;}
    int aa=-0x7f7f7f7f;
    int bb=-0x7f7f7f7f;
    bb=dfs(i+1,j);
    if(j>=w[i])aa=dfs(i+1,j-w[i])+v[i];
    mo[i][j]=max(aa,bb);
    return mo[i][j];
}
int main(){
    cin>>W>>n;
    memset(mo,-1,sizeof(mo));
    for(int i=1;i<=n;++i)cin>>w[i]>>v[i];
    cout<<dfs(1,W);
    return 0;
}