#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool Isprime(int t)
{
	for(int i=2;i<=t-1;++i)
		if (t%i==0)return 1;
	return 0;
}
int main()
{
	cin>>n;
	if(Isprime(n))	cout<<"��������"<<endl;
	else	cout<<"������"<<endl;
	
	
	
	
	return 0;
}
