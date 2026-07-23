#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[30]={0},b[30]={0},t[90]={0};
    string aa,bb;
    cin>>aa>>bb;
    for(int i=0;i<aa.size();++i){
        a[aa.size()-i-1]=aa[i]-'0';
    }
    for(int i=0;i<bb.size();++i){
        b[bb.size()-i-1]=bb[i]-'0';
    }
    int k=max(aa.size(),bb.size());
    for(int i=0;i<k;++i){
        int sum=t[i]+a[i]+b[i];
        t[i]=sum%10;
        t[i+1]=sum/10;
    }
    if(t[k]>0)k++;
    for(int i=k-1;i>=0;--i)cout<<t[i];
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[30]={0},b[30]={0},t[90]={0};
    string aa,bb;
    cin>>aa>>bb;
    for(int i=0;i<aa.size();++i){
        a[aa.size()-i-1]=aa[i]-'0';
    }
    for(int i=0;i<bb.size();++i){
        b[bb.size()-i-1]=bb[i]-'0';
    }
    int k=max(aa.size(),bb.size());
    for(int i=0;i<k;++i){
        int sum=t[i]+a[i]+b[i];
        t[i]=sum%10;
        t[i+1]=sum/10;
    }
    if(t[k]>0)k++;
    for(int i=k-1;i>=0;--i)cout<<t[i];
    return 0;
}