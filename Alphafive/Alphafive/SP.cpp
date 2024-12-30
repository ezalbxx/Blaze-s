//1Ϊ���ӣ�2Ϊ����
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
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void ScreenPrint_setting()
{
	loadimage(&img_bk,"C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\qiapn3.png",800,600);
	loadimage(&img_white, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\white1.png",37,37);
	loadimage(&img_black, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\black.png",37,37);
	loadimage(&img_victory, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\victory.png", 800, 600);
	loadimage(&img_defeat, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\defeat.png", 800, 600);
	//loadimage(&img_mouse_touched, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\mouse_touched.png", 30, 30);
	//loadimage(&img_mouse_untouched, "C:\\Users\\��һ��\\source\\repos\\Alphafive\\Alphafive\\mouse_untouched.png", 30, 30);
	initgraph(800, 600);//��ӻ�ͼ����
	setbkcolor(TRANSPARENT);
	cleardevice();
	putimage(0, 0, &img_bk);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	drawAlpha(&img_black, 19, 19);//��19+��n-1)*30
	drawAlpha(&img_white,72, 50);//��19+��n-1��*53
	//closegraph();�رջ�ͼ����
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
		outtextxy(600, 13, "AI����˼���С���");
		Sleep(100);
	}
	if (s == 2)
	{
		outtextxy(600, 13, "�ֵ��������ˣ�");
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

