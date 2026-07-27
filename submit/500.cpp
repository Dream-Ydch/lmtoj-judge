#include <iostream>
#include <algorithm>
using namespace std;

int a[1001000];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
    sort(a+1,a+n+1,greater<int>());
    for (int i = n; i>=1; i--)
	{
		cout << a[i] << " ";
	}
	return 0;
}