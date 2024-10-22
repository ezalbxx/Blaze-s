#include<iostream>
#include<cstdio>
#include"stdlib.h"
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
int map[31][31];
int x = 2, y = 2, endx = 29, endy = 29,Count=101;

void MapBuild();//地图绘制
void ScreenPrint(int x, int y);//显示操作
char Get();//输入
void Move(char c);//移动的计算


char Get()
{
	char c = _getch();
	return c;
}

void MapBuild()
{
	for (int i = 0; i <= 30; ++i)
	{
		map[i][0] = 1;
		map[i][30] = 1;
		map[0][i] = 1;
		map[30][i] = 1;
	}
	map[13][13] = 1;
	map[29][16] = 1;
	srand((unsigned)time(NULL));//随机数种子 
	for (int i = 0; i < 200; i++)//生成200个方块 
	{
		map[rand() % 31 + 1][rand() % 31 + 1] = 1;//随机在某个位置生成方块 
	}
	map[29][29] = 0;
	map[29][28] = 0;
	map[28][29] = 0;
	map[29][27] = 0;
	map[27][29] = 0;
	map[28][28] = 0;
	return;
}

void ScreenPrint(int x, int y)
{

	system("cls");
	for (int i = 0; i <= 30; ++i)
	{
		for (int j = 0; j <= 30; ++j)
		{
			if (map[i][j] == 1)	cout << "墙";
			if (map[i][j] == 2)	cout << "人";
			if (map[i][j] == 0)	cout << "  ";
			if (map[i][j] == 3)	cout << "箱";
		}
		cout << endl;
	}
	Sleep(50);
	return;
}

void Move(char c)
{
	if (c == 'a' && map[x][y - 1] == 0)
	{
		map[x][y] = 0;
		map[x][y - 1] = 2;
		y = y - 1;
	}
	if (c == 'd' && map[x][y + 1] == 0)
	{
		map[x][y] = 0;
		map[x][y + 1] = 2;
		y = y + 1;
	}
	if (c == 'w' && map[x - 1][y] == 0)
	{
		map[x][y] = 0;
		map[x - 1][y] = 2;
		x = x - 1;
	}
	if (c == 's' && map[x + 1][y] == 0)
	{
		map[x][y] = 0;
		map[x + 1][y] = 2;
		x = x + 1;
	}


	if (c == 'a' && map[x][y - 1] == 3)
	{
		if (map[x][y - 2] == 0)
		{
			map[x][y] = 0;
			map[x][y - 1] = 2;
			map[x][y - 2] = 3;
			y = y - 1;
		}
	}
	if (c == 'd' && map[x][y + 1] == 3)
	{
		if (map[x][y + 2] == 0)
		{
			map[x][y] = 0;
			map[x][y + 1] = 2;
			map[x][y + 2] = 3;
			y = y + 1;
		}
	}
	if (c == 'w' && map[x-1][y ] == 3)
	{
		if (map[x-2][y] == 0)
		{
			map[x][y] = 0;
			map[x-1][y ] = 2;
			map[x-2][y ] = 3;
			x = x - 1;
		}
	}
	if (c == 's' && map[x+1][y ] == 3)
	{
		if (map[x+2][y] == 0)
		{
			map[x][y] = 0;
			map[x+1][y] = 2;
			map[x+2][y] = 3;
			x = x + 1;
		}
	}
	return;
}

bool isPlay()
{
	if (map[29][29]==3)	return	false;
	Count -= 1;
	map[x][y] = 2;
	ScreenPrint(x, y);
	printf("\n score:%d", Count);
	char c = Get();
	Move(c);


	return true;
}

int main()
{
	MapBuild();
	double dur;
	clock_t start, end;
	start = clock();
	map[3][3] = 3;
	while (isPlay())
	{

	}
	end = clock();
	system("cls");
	printf("You Win!\n");
	dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
	printf("Score:%d\n", Count);
	Sleep(200000);

	return 0;
}