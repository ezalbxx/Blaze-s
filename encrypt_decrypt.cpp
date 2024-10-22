#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string encrypt(string a)
{
	for (int i = 0; i < a.size(); ++i)
		a[i] = a[i] + 5;
	return a;
}
string decrypt(string a)
{
	for (int i = 0; i < a.size(); ++i)
		a[i] = a[i] - 5;
	return a;
}
int main()
{
	string s;
	cin >> s;
	cout << encrypt(s)<<endl;
	cout << decrypt(s)<<endl;


	return 0;
}