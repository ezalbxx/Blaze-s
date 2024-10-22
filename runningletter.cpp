#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
char a;
void HideCursor()
{ CONSOLE_CURSOR_INFO cursor_info = {1, 0};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int main()
{
	HideCursor();
	cin>>a;
	system("cls");
	for(int i=1;i<=119;++i)
	{
	
		for(int j=1;j<=i;++j)
			cout<<' ';
		cout<<a;Sleep(100);
		system("cls");
		
	}
	for(int i=118;i>=1;--i)
	{
	
		for(int j=1;j<=i;++j)
			cout<<' ';
		cout<<a;Sleep(100);
		system("cls");
		
	}
	cout<<a;	
	
	
	return 0;
}
