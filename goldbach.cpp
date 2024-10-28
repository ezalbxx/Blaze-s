#include<iostream>
#include<cstdio>
using namespace std;
int a[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int main()
{
	for(int t=6;t<=100;++t)
		for(int i=0;i<=24;++i)
			for(int j=i+1;j<=24;++j)
				for(int z=j+1;z<=24;++z)
					if(t==a[i]+a[j]+a[z])
						cout<<t<<"="<<a[i]<<"+"<<a[j]<<"+"<<a[z]<<endl;
	
	
	
	return 0;
}
