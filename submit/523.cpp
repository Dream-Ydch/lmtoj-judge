#include<bits/stdc++.h>
using namespace std;
int a[100001];
void qsort(int left,int right){
	int i=left,j=right;
	int mid=a[(i+j)/2];
	while(i<=j){
		while(a[i]<mid)i++;
		while(a[j]>mid)j--;
		if(i<=j){
			swap(a[i],a[j]);
			i++;
			j--;
		}
	}
	if(i<right)qsort(i,right);
	if(j>left) qsort(left,j);
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<=n-1;i++)cin>>a[i];
	qsort(0,n-1);
	for(int i=0;i<=n-1;i++){
        if(i!=0)cout<<' ';
        cout<<a[i];
    }
	return 0;
}