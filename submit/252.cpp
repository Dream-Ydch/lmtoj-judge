#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=1e5+1;
int n,m;
struct Point{
	int sum;
	int l,r;
	int add;
}tree[N*4];
int a[N];
void pushup(int x){
	tree[x].sum=tree[2*x].sum+tree[2*x+1].sum;
}
void build(int x,int l,int r){
	tree[x].l=l;
	tree[x].r=r;
	tree[x].add=0;
	if(l==r){
		tree[x].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	pushup(x);
}
void pushdown(int x){
	if(tree[x].add){
		tree[x*2].add+=tree[x].add;
		tree[x*2+1].add+=tree[x].add;
		tree[2*x].sum+=tree[x].add*(tree[2*x].r-tree[2*x].l+1);
		tree[2*x+1].sum+=tree[x].add*(tree[2*x+1].r-tree[2*x+1].l+1);
		tree[x].add=0;
	}
}
int query(int x,int l,int r){
	if(l<=tree[x].l&&r>=tree[x].r){
		return tree[x].sum;
	}
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)/2;
	int sum=0;
	if(l<=mid){
		sum+=query(x*2,l,r);
	}
	if(r>mid){
		sum+=query(x*2+1,l,r);
	}
	return sum;
}
void update(int now,int l,int r,int k){
	if(l<=tree[now].l&&r>=tree[now].r){
		tree[now].sum+=k*(tree[now].r-tree[now].l+1);
		tree[now].add+=k;
	}else{
		pushdown(now);
		int mid=(tree[now].l+tree[now].r)>>1;
		if(l<=mid){
			update(now*2,l,r,k);
		}
		if(r>mid){
			update(now*2+1,l,r,k);
		}
		pushup(now);
	}
}
signed main(){
	cin>>n>>m;
	build(1,1,100000);
	update(1,1,1,n);
    update(1,1,1,m);
	cout<<query(1,1,1);
	return 0;
}