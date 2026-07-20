#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=25;
const double eps=1e-8,INF=1e15;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
	return x*f;
}
int n,m,type;
double a[N][N],ans[N];
int id[N<<1];
int q[N];
void Pivot(int l,int e){
	swap(id[n+l],id[e]);
	double t=a[l][e]; a[l][e]=1;
	for(int j=0;j<=n;j++) a[l][j]/=t;
	for(int i=0;i<=m;i++) if(i!=l && abs(a[i][e])>eps){
		t=a[i][e]; a[i][e]=0;
		for(int j=0;j<=n;j++) a[i][j]-=a[l][j]*t;
	}
}
bool init(){
	while(true){
		int e=0,l=0;
		for(int i=1;i<=m;i++) if(a[i][0]<-eps && (!l||(rand()&1))) l=i;
		if(!l) break;
		for(int j=1;j<=n;j++) if(a[l][j]<-eps && (!e||(rand()&1))) e=j;
		if(!e) {puts("Infeasible");return false;}
		Pivot(l,e);
	}
	return true;
}
bool simplex(){
	while(true){
		int l=0,e=0; double mn=INF;
		for(int j=1;j<=n;j++)
			if(a[0][j]>eps) {e=j;break;}
		if(!e) break;
		for(int i=1;i<=m;i++) if(a[i][e]>eps && a[i][0]/a[i][e]<mn)
			mn=a[i][0]/a[i][e],l=i;
		if(!l) {puts("Unbounded");return false;}
		Pivot(l,e);
	}
	return true;
}
int main(){
	srand(317);
	n=2,m=2;
	int A=read()+1E9,B=read()+1E9;
	a[0][1]=1,a[0][2]=1;
	a[1][0]=A,a[1][1]=1,a[1][2]=0;
	a[2][0]=B,a[2][1]=0,a[2][2]=1;
	for(int i=1;i<=n;i++) id[i]=i;
	if(init() && simplex()){
		printf("%.0lf\n",-a[0][0]-2E9);
	}
	else exit(-1);
}