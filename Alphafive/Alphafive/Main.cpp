#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<graphics.h>

using namespace std;
#define Infinity 10000000
int a[16][16];//���̣��ո�Ϊ0��AI����Ϊ1��Player����Ϊ2
bool f[16][16],Aivictory=false,Playervictory=false;
int search_x_right, search_x_left, search_y_up, search_y_down;
void paint()
{
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
			f[i][j] = false;
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
		{
			if (a[i][j] !=0)
			{
				if (i - 1 >= 1 && a[i - 1][j] == 0)	f[i - 1][j] = true;
				if (i + 1 <= 15 && a[i + 1][j] == 0)	f[i + 1][j] = true;
				if (j - 1 >= 1 && a[i][j - 1] == 0)	f[i][j - 1] = true;
				if (j + 1 <= 15 && a[i][j + 1] == 0)	f[i][j + 1] = true;
			}
		}

	return;
}
void count()
{
	int count = 0, x_l = 16, x_r = 0, y_u = 16, y_d = 0;
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
			if (a[i][j] != 0)
			{
				count++;
				if (j < x_l)	x_l = j;
				if (j > x_r)	x_r = j;
				if (i < y_u)	y_u = i;
				if (i > y_d)	y_d = i;
			}
	search_x_right = x_r + 1;
	search_x_left = x_l - 1;
	search_y_down = y_d + 1;
	search_y_up = y_u - 1;
	if (search_x_right > 15)	search_x_right = 15;
	if (search_x_left < 1)	search_x_left = 1;
	if (search_y_up < 1)	search_y_up = 1;
	if (search_y_down > 15)	search_y_down = 15;
	return;
}
struct position {
	int x;
	int y;
};

int Max(int a, int b, int c,int d)
{
	int maxx;
	if (a > b)	maxx = a;
	else maxx = b;
	if (c > maxx)	maxx = c;
	if (d > maxx)	maxx = d;
	return maxx;
}
//����

extern void ScreenPrint(int s);
extern void ScreenPrint_setting();

//��������ֵģ��
string Findright(int x, int y)
{
	if (x + 5 > 15 )
	{
		string s = "00000";
		return s;
	}
	string s;
	for (int i = x; i <= x + 4; ++i)
		s += char(a[i][y] + 48);
	return s;
}
string Finddown(int x, int y)
{
	if (y + 5 > 15 )
	{
		string s = "00000";
		return s;
	}
	string s;
	for (int i = y; i <= y + 4; ++i)
		s += char(a[x][i] + 48);
	return s;
}
string Findrd(int x, int y)
{
	if (x + 5 > 15 || y + 5 > 15)
	{
		string s = "00000";
		return s;
	}
	string s;
	for (int i = x, j = y; i <= x + 4, j <= y + 4; ++i, ++j)
		s += char(a[i][j] + 48);
	return s;
}
string Findld(int x, int y)
{
	if (x - 4 <= 0 || y - 4 <= 0)
	{
		string s = "00000";
		return s;
	}
	string s;
	int xx = x - 4, yy = y - 4;
	int i = x, j = y;
	while (i >= xx && j >= yy)
	{
		s += char(a[i][j]+48);
		i -= 1;
		j -= 1;
	}
	return s;
}
//�ĸ����Һ�����������ȡ���������ϵ��ַ���
int Match_1(string s)
{
	if (s == "21110")	return 80;
	if (s == "01112")	return 80;
	if (s == "21112")	return 0;
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == '2')
			s[i] = '0';
	if (s == "00000") return	0;
	if (s == "00001") return	5;
	if (s == "00010") return	5;
	if (s == "00011") return	80;
	if (s == "00100") return	5;
	if (s == "00101") return	60;
	if (s == "00110") return	100;
	if (s == "00111") return	500;
	if (s == "01000") return	5;
	if (s == "01001") return	20;
	if (s == "01010") return	80;
	if (s == "01011") return	500;
	if (s == "01100") return	100;
	if (s == "01101") return	500;
	if (s == "01110") return	80000;
	if (s == "01111") return	100000;
	if (s == "10000") return	5;
	if (s == "10001") return	10;
	if (s == "10010") return	20;
	if (s == "10011") return	600;
	if (s == "10100") return	50;
	if (s == "10101") return	600;
	if (s == "10110") return	500;
	if (s == "10111") return	5000;
	if (s == "11000") return	80;
	if (s == "11001") return	600;
	if (s == "11010") return	500;
	if (s == "11011") return	6000;
	if (s == "11100") return	500;
	if (s == "11101") return	5000;
	if (s == "11110") return	100000;
	if (s == "11111") return	Infinity;
}
int Match_2(string s)
{
	if (s == "02221")	return 80;
	if (s == "12220")	return 80;
	if (s == "12221")	return 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '1')
			s[i] = '0';
		if (s[i] == '2')
			s[i] = '1';
	}
	if (s == "00000") return	0;
	if (s == "00001") return	5;
	if (s == "00010") return	5;
	if (s == "00011") return	80;
	if (s == "00100") return	5;
	if (s == "00101") return	60;
	if (s == "00110") return	100;
	if (s == "00111") return	500;
	if (s == "01000") return	5;
	if (s == "01001") return	20;
	if (s == "01010") return	80;
	if (s == "01011") return	500;
	if (s == "01100") return	100;
	if (s == "01101") return	500;
	if (s == "01110") return	800000;
	if (s == "01111") return	1000000;
	if (s == "10000") return	5;
	if (s == "10001") return	10;
	if (s == "10010") return	20;
	if (s == "10011") return	600;
	if (s == "10100") return	50;
	if (s == "10101") return	600;
	if (s == "10110") return	500;
	if (s == "10111") return	5000;
	if (s == "11000") return	80;
	if (s == "11001") return	600;
	if (s == "11010") return	500;
	if (s == "11011") return	6000;
	if (s == "11100") return	500;
	if (s == "11101") return	5000;
	if (s == "11110") return	1000000;
	if (s == "11111") return	Infinity;
}
//����Player�����ͽ��й�ֵ
int Find(int x, int y, int who)
{
	int value = 0;
	string s1, s2, s3, s4;
	s1 = Findright(x, y);
	s2 = Finddown(x, y);
	s3 = Findrd(x, y);
	s4 = Findld(x, y);
	if (who == 1)
	{
		int a1 = Match_1(s1);
		int a2 = Match_1(s2);
		int a3 = Match_1(s3);
		int a4 = Match_1(s4);
		value = Max(a1, a2, a3,a4);
		return value;
	}//AI��λ��ֵ
	if (who == 2)
	{
		int a1 = Match_2(s1);
		int a2 = Match_2(s2);
		int a3 = Match_2(s3);
		int a4 = Match_2(s4);
		value = Max(a1, a2, a3,a4);
		return value * 5;
	}
	return value;
}//ĳ����λ�ϵļ�ֵ
//���Һ��������ڶ�ĳ��λ�ý��й�ֵ
int evaluate()
{
	int valueAi = -Infinity, valuePlayer = -Infinity;
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
			//	if(a[i][j]!=0)
		{
			int aa = Find(i, j, 1);
			if (aa > valueAi)	valueAi = aa;
		}//��AI�ľ�����й�ֵ
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
			//	if(a[i][j]!=0)
		{
			int aa = Find(i, j, 2);
			if (aa > valuePlayer)	valuePlayer = aa;
		}//��Player�ľ�����й�ֵ
	return valueAi - valuePlayer;
}

//����AI�ж�ģ��

int Search(int alpha, int beta, int depth) {
	if (depth == 4)
	{
		return evaluate();
	} // �������յ㣬�����ʵ��������� evaluate �Ĳ�������
	count();
	paint();
	if (depth % 2 == 1)
	{ // Min �㣬Player ����
		int x;
		bool flag = false;
		for (int i = search_y_up; i <= search_y_down; ++i)
		{
			for (int j = search_x_left; j <= search_x_right; ++j)
				if (f[i][j] == true)
				{
					if (a[i][j] == 0)
					{
						a[i][j] = 2;
						x = Search(alpha, beta, depth + 1);
						a[i][j] = 0;
						if (x < beta) beta = x;
						if (alpha >= beta)
						{
							flag = true;
							break;
						}
					}
				}
			if (flag)	break;
		}
		return beta;
	}
	if (depth % 2 == 0)
	{ // Max �㣬Ai ����
		int x;
		for (int i = search_y_up; i <= search_y_down; ++i)
		{
			bool flag = false;
			for (int j = search_x_left; j <= search_x_right; ++j)
				if (f[i][j] == true)
				{
					if (a[i][j] == 0)
					{
						a[i][j] = 1;
						x = Search(alpha, beta, depth + 1);
																		//		cout << x << endl;
						a[i][j] = 0;
						if (x > alpha) alpha = x;
						if (alpha >= beta)
						{
							flag = true;
							break;
						}
					}
				}
			if (flag)	break;
		}
		return alpha;
	}
	return 0; // ������뾯�棬�ɸ���ʵ�������������ֵ
}

position Search_1()//alpha������½磬beta����С�Ͻ� 
{
	position t;
	int max = -Infinity;
	count();
	paint();
	for (int i = search_y_up; i <= search_y_down; ++i)
		for (int j = search_x_left; j <= search_x_right; ++j)
			if (a[i][j] == 0&&f[i][j]==true)
			{
				a[i][j] = 1;
				int z = Search(-Infinity, Infinity, 1);
				a[i][j] = 0;
				if (z > max)
				{
					max = z;
					t.x = i;
					t.y = j;
				}
			}
	return t;
}
//��һ�ε����� 
//�Ĳ��������AI��һ���ж�
void AIGO()
{
	position t;
	t = Search_1();
	a[t.x][t.y] = 1;
	return;
}//�����ѵ�һ���֣�AI�������λ��



//����ʤ���ж�ģ��
bool isVictory(int t)
{
	for(int i=1;i<=15;++i)
		for (int j = 1; j <= 15; ++j)
		{
			string s1, s2, s3, s4;
			s1 = Findright(i, j);
			s2 = Finddown(i, j);
			s3 = Findrd(i, j);
			s4 = Findld(i, j);
			if (s1 == "11111" || s2 == "11111" || s3 == "11111" || s4 == "11111")	Aivictory = true;
			if (s1 == "22222" || s2 == "22222" || s3 == "22222" || s4 == "22222")	Playervictory = true;
		}
	if (t == 1 && Aivictory)	return true;
	if (t == 2 && Playervictory)	return true;
	return false;
}

//������Ϸ������ģ��
bool isPlay()
{
	ScreenPrint(2);
	//PlayerGo();
	ScreenPrint(0);
	if (isVictory(2))
	{
		ScreenPrint(22);
		return false;
	}
	ScreenPrint(1);
	AIGO();
	ScreenPrint(0);
	if (isVictory(1))
	{
		ScreenPrint(11);
		return false;
	}
	return true;
}

int main()
{
	ScreenPrint_setting();
	while (isPlay())
	{

	}

	




	return 0;
}