#include<iostream>
#include<cstdio>
#include<time.h>
using namespace std;
bool Isprime(int a)
{
	int b=a/3;
	for(int i=3;i<=b+1;++i)
		if(a%i==0)	return	false;
	return true; 
}
int main()
{
	clock_t start,end;
	start=clock();
	int count=1;
	cout<<'2'<<' ';
	for(int i=3;i<=997;i+=2)
		if(Isprime(i))	
			cout<<i<<' ';
	end=clock();
	cout<<endl;
	cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	return 0;
}
