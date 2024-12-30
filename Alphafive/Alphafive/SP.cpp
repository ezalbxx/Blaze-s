//1为黑子，2为白子
#include<iostream>
#include<cstdio>
#include<cstring>
#include<graphics.h>
#include<windows.h>
#include<easyx.h>
#include<conio.h>
using namespace std;
IMAGE img_bk, img_white, img_black,img_victory,img_defeat,img_mouse_touched,img_mouse_untouched;
bool flag = false;
extern int a[16][16];
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void ScreenPrint_setting()
{
	loadimage(&img_bk,"C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\qiapn3.png",800,600);
	loadimage(&img_white, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\white1.png",37,37);
	loadimage(&img_black, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\black.png",37,37);
	loadimage(&img_victory, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\victory.png", 800, 600);
	loadimage(&img_defeat, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\defeat.png", 800, 600);
	//loadimage(&img_mouse_touched, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\mouse_touched.png", 30, 30);
	//loadimage(&img_mouse_untouched, "C:\\Users\\骆一鸣\\source\\repos\\Alphafive\\Alphafive\\mouse_untouched.png", 30, 30);
	initgraph(800, 600);//添加绘图窗体
	setbkcolor(TRANSPARENT);
	cleardevice();
	putimage(0, 0, &img_bk);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	drawAlpha(&img_black, 19, 19);//行19+（n-1)*30
	drawAlpha(&img_white,72, 50);//列19+（n-1）*53
	//closegraph();关闭绘图窗体
}

void Reset()
{
	putimage(0, 0, &img_bk);
	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= 15; ++j)
		{
			if (a[j][i] == 1)
				drawAlpha(&img_black, 19 + (i - 1) * 51.7, 19 + (j - 1) * 39);
			if (a[j][i] == 2)
				drawAlpha(&img_white, 19 + (i - 1) * 51.7, 19 + (j - 1) * 39);
		}
}

void Mousetouch()
{
	//BeginBatchDraw();
	bool flag = true;
	while (flag)
	{
		int x, y;
		ExMessage msg;
		while (peekmessage(&msg)) {
			 if (msg.message == WM_LBUTTONDOWN)
			{
				x = msg.x;
				y = msg.y;
				int xx = (x - 19) / 51.7 + 1;
				int yy = (y - 19) / 39 + 1;
				a[yy][xx] = 2;
				flag = false;
				break;
			}
		//	FlushBatchDraw();
		}
	}
	//EndBatchDraw();
	
}

void ScreenPrint(int s)
{
	Reset();
	if (s == 1)
	{
		outtextxy(600, 13, "AI正在思考中……");
		Sleep(100);
	}
	if (s == 2)
	{
		outtextxy(600, 13, "轮到您落子了！");
		Mousetouch();
		Sleep(100);
	}
	if (s == 11)
	{
		putimage(0, 0, &img_defeat);
		Sleep(10000);
	}
	if (s == 22)
	{
		putimage(0, 0, &img_victory);
		Sleep(10000);
	}
}

