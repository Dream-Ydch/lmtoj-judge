#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
//十年OI一场空，不开long long见祖宗
int T , M;
int v[101] , w[101] , f[101][1001];
int main(){
	scanf("%d%d" , &T , &M);
	for(int i = 1 ; i <= M ; i++)
		scanf("%d%d" , &v[i] , &w[i]);
	memset(f , 0 , sizeof(f));
	for(int i = 1 ; i <= M ; i++){
		for(int j = 0;j <= T ; j++){
			if(j < v[i])
				f[i][j]= f[i - 1][j];
			else
				f[i][j] = max(f[i - 1][j] , f[i - 1][j - v[i]] + w[i]);
		}
	}
	printf("%d" , f[M][T]);
	return 0;
}