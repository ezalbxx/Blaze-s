#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

typedef struct Node{
	int data;
	Node * next=NULL;
}Node;

Node *head,*tail=NULL;

void Add(int data1)
{
	Node * p=(Node*)malloc(sizeof(Node));
	p->data=data1;
	p->next=NULL;
	if(tail!=NULL)
		tail->next=p;
	tail=p;
	return;
}//�������β��������Ԫ�� 

void Look()
{
	Node * p;
	p=head;
	while(p->next!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	printf("%d\n",p->data);
	return;
}//������������ 

int Find()
{
	Node * p;
	p=head;
	int count=1;
	while(p->next!=NULL)
	{
		if(p->data==5)	
			return count;
		count++;
		p=p->next;
	}
	return -1;
}//��5 

int Find2()
{
	Node * p;
	p=head;
	int count=1,count2=0;
	while(p->next!=NULL)
	{	
		count++;
		if(p->data==5)	count2++;
		if(count2==2)	return count;
		p=p->next;
	}
	if(p->data==5&&count2==1)	return count;
	return -1;
}//��5 2

struct Node* reserve(struct Node* head)
{
	Node *p1,*p2,*p3;
	p2=head;
	p3=p2->next;
	while(p3!=NULL)
	{
		p1=p2;
		p2=p3;
		p3=p2->next;
		p2->next=p1;
	}
	head->next=NULL;//�ؼ�����ֹ��ѭ�� 
	return p2;
}//���� 

int main()
{
	head=NULL;
	Add(1);
	head=tail;
	Add(2);
	Add(3);
	Add(4);
	Add(5);
	Add(6);
	Add(7);
	Add(5);//���������� 

	Look();//���� 

	head=reserve(head);//���� 
	
	printf("%d\n",Find());
	printf("%d\n",Find2());//��5 + ��5��2�� 
	
	return 0;
}
