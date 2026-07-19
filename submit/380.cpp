#include<bits/stdc++.h>
using namespace std;int main(){
int a;cin>>a;int b[100007];for(int i=0;i<a;++i)cin>>b[i];sort(b,b+a);for(int i=0;i<a;++i)cout<<b[i]<<' ';cout<<endl;return 0;}