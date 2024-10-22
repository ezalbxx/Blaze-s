#include<iostream>
#include<cstdio>
using namespace std;
void hanoi(int start,int end,int tra,int count)
{
	if(count==0)	return;
	hanoi(start,tra,end,count-1);
	cout<<"from"<<start<<"to"<<end<<endl;
	hanoi(tra,end,start,count-1);
}
int main()
{
	hanoi(1,2,3,4);
	
	
	
	
	return 0;
}
