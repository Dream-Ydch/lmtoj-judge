#include<iostream>
using namespace std;
inline int readint(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+(c-='0');
		c=getchar();
	}
	return x*f;
}
inline void writeint(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)writeint(x/10);
	putchar(x%10+'0');
}
int a,b;
signed main(){
	a=readint();
	b=readint();
	writeint(a+b);
	return 0;
}