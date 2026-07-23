#include <bits/stdc++.h>
using namespace std;
int T,N;
int v[110],w[110],f[1010];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> T >> N;
    for(int i=1;i<=N;i++){
        cin >> v[i] >> w[i];
    }
    for(int i=1;i<=N;i++){
        for(int j=T;j>=v[i];j--){
            f[j]=max(f[j], f[j-v[i]]+w[i]);
        }
    }
    cout << f[T] << endl;
}