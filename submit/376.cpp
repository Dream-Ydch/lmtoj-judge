#include<bits/stdc++.h>
using namespace std;
long long n,a[100005];
void qsort(int low,int high){
    if(low < high){
        int tmp = (low + high) / 2;
        int t = a[low];
        a[low] = a[tmp];
        a[tmp] = t;
        int x = a[low];
        int i = low + 1;
        int j = high;
        while(true){
            while(i <= high && a[i] < x)++i;
            while(j >= low && a[j] > x)--j;
            if(i >= j)break;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
            ++i;
            --j;
        }
        t=a[low];
        a[low]=a[j];
        a[j]=t;
        if(low < j - 1){
            qsort(low,j - 1);
        }
        if(j + 1 < high){
            qsort(j + 1,high);
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d",&a[i]);
    }
    qsort(0,n-1);
    for(int i=0;i<n;++i){
        printf("%d ",a[i]);
    }
    // printf("\n");
    return 0;
}