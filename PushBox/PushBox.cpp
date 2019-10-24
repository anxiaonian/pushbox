#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<Windows.h>
#include"resource.h"
#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define RPow 7
#define CPol 8
HWND hWnd;
int win;
int map[RPow][CPol] = {
		{ 0,1,1,1,1,1,1,0 },  //0表示空地
		{ 0,1,0,0,0,0,1,1 },  //1是墙
		{ 1,1,3,1,1,4,0,1 },  //3是目的地
		{ 1,0,3,3,4,0,0,1 },  //4是箱子
		{ 1,0,0,1,4,0,0,1 },  //5是人
		{ 1,0,0,5,0,1,1,1 },
		{ 1,1,1,1,1,1,0,0 }
	};

	void Game();
	void draw(IMAGE img[], int map[][CPol]);       //,int map[][CPol +2]
	int Move(int map[][CPol]);

	//主函数
	int main() {
	
		//mciSendString(L"")
		PlaySound((LPCTSTR)IDR_WAVE1, 0, SND_RESOURCE | SND_ASYNC);
		while (1) {
			system("cls");
			Game();
		/*	if (MessageBox(hWnd, L"下一关?", L"退出", MB_RETRYCANCEL) == IDCANCEL) {
				break ;
			}*/
		}
		//closegraph;
		return 0;
	}
	//遍历数组
	//void DrawMap() {
	//	for (int i = 0; i < RPow; i++)
	//	{
	//		for (int j = 0; j < CPow; j++) {
	//			//printf("%d",map[i][j]);
	//			
	//			switch (map[i][j])
	//			{
	//			case 0:
	//				printf("  ");
	//				break;
	//			case 1:
	//				printf("■");
	//				break;
	//			case 3:
	//				printf("☆");
	//				break;
	//			case 4:
	//				printf("□");
	//				break;
	//			case 5:
	//				printf("♀");
	//				break;
	//			case 7:
	//				printf("★");   //箱子和目的地
	//				break;
	//			case 8:
	//				printf("♀");    //人和目的地
	//				break;
	//				//default:
	//				//break;
	//			}
	//		}
	//		printf("\n");
	//	}
	//}
	
	void Game(){
	
	/*	for (int i = 0; i < RPow+2; i++)
		{
		for (int j = 0; j < CPol +2; j++) {
				printf("%4d", map[i][j]);
				
			}
			printf("\n");
		}
*/
		
      //做界面670*680//  512, 448
		initgraph(512,448);
     //加载图片
		IMAGE img[5];

		//从当前项目文件夹目录下加载图片
	/*	loadimage(&img[0], L"00.jpg", 64, 64);
		loadimage(&img[1], L"01.jpg",64, 64);
		loadimage(&img[2], L"03.jpg", 64, 64);
		loadimage(&img[3], L"04.jpg",64, 64);
		loadimage(&img[4], _T("05.jpg"), 64, 64);*/

		//从资源文件加载图片
		loadimage(&img[0], L"JPG", MAKEINTRESOURCE(100), 64, 64);
		loadimage(&img[1], L"JPG", MAKEINTRESOURCE(101), 64, 64);
		loadimage(&img[2], L"JPG", MAKEINTRESOURCE(103), 64, 64);
		loadimage(&img[3], L"JPG", MAKEINTRESOURCE(104), 64, 64);
		loadimage(&img[4], _T("JPG"),MAKEINTRESOURCE(105), 64, 64);
	
		win = 0;
		//贴图部分
		while (1) {
			draw(img, map);
			Move(map);
		for (int i = 0; i < RPow; i++)
		{
			for (int j = 0; j < CPol; j++) {
				if (map[i][j] == 7)
				{win++;}
				}
		}
		if (win != 3) { win = 0; }
		else {
			draw(img, map);
			MessageBox(hWnd, L"你赢了", L"消息窗口", MB_OK);
			break;
		}
	}
		return;
	}
				
    void draw(IMAGE img[],int map[][CPol]){          //int map[][CPol +2]
		
		for (int i = 0; i < RPow; i++)
			{
				for (int j = 0; j < CPol+1 ; j++) {
					//putimage (64 * i - 64, 64 * j - 64, &img[map[i][j]]);
					switch (map[i][j])
							{
				        	case 0: putimage(64 * j , 64 * i, &img[0]);
					        	break;
								
							case 1: putimage(64 * j , 64* i, &img[1]);
							//	printf("■");
								break;
								
							case 3:	putimage(64 * j , 64 * i, &img[2]);
							//	printf("☆");
								break;
							
							case 4:	putimage(64 * j, 64 * i, &img[3]);
							//	printf("□");
								break;
							
							case 5: putimage(64 * j , 64 * i, &img[4]);
								//printf("♀");
								break;
								
							case 7:	putimage(64 * j, 64 * i, &img[3]);
								//printf("★");   //箱子和目的地
								break;

							case 8:	putimage(64 * j, 64 * i, &img[4]);
								//printf("♀");    //人和目的地
								break;
								default:
								break;
							}
						}
						//printf("\n");
					}
				}
			

	
	//移动
	int Move(int map[][CPol]) {
		char ch;
		int i, j;
		int r, c;       //人的坐标
		ch = _getch();   //需加载<conio.h>头文件,直接接收字符,不用按回车
		for (i = 0; i < RPow; i++)
		{
			for (j = 0; j < CPol; j++)
			{
				if (map[i][j] == 5 || map[i][j] == 8)
				{
					r = i;
					c = j;
				}
			}
			if (map[i][j] == 5 || map[i][j] == 8)  //判断人在目的地
				break;
		}

		switch (ch)
		{
		case VK_UP:
		case'w':         //上
		case'W':
		case 72:        //键值
						//人的坐标 map[r][c], 人上一个位置 map[r-1][c] 是否为空地0或目的地3,是就交换值
			if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
			{
				map[r - 1][c] += 5;    //人向上移动
				map[r][c] -= 5;        //原位置变回空地0 
			}
			else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
			{
				if (map[r - 2][c] == 0 || map[r - 2][c] == 3)   //箱子前面 map[r-2][c]是否为空地或目的地
				{
					map[r - 2][c] += 4;       //箱子向上移动
					map[r - 1][c] += 1;       //人移动到原箱子位置
					map[r][c] -= 5;           //原先的人位置变为空地0
			
				}
			}


			//	if (map[r - 1][c] == 0)
			//	{
			//		map[r - 1][c] += 5;    //人向上移动
			//		map[r][c] -= 5;        //原位置变回空地0 
			//}
			//	else if (map[r - 1][c] == 3)        //人5的前面是目的地
			//	{
			//		map[r - 1][c] += 8;   
			//		map[r][c] -= 5;
			//	}
			break;

		case VK_DOWN:
		case's':         //下
		case'S':
		case 80:
			if (map[r + 1][c] == 0 || map[r + 1][c] == 3)
			{
				map[r + 1][c] += 5;    //人向上移动
				map[r][c] -= 5;        //原位置变回空地0 
			}
			else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
			{
				if (map[r + 2][c] == 0 || map[r + 2][c] == 3)   //箱子前面 map[r-2][c]是否为空地或目的地
				{
					map[r + 2][c] += 4;       //箱子向上移动
					map[r + 1][c] += 1;       //人移动到原箱子位置
					map[r][c] -= 5;           //原先的人位置变为空地0
				}
			}

			break;

		case VK_LEFT:
		case'a':         //左
		case'A':
		case 75:
			if (map[r][c - 1] == 0 || map[r][c - 1] == 3)
			{
				map[r][c - 1] += 5;    //人向上移动
				map[r][c] -= 5;        //原位置变回空地0 
			}
			else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
			{
				if (map[r][c - 2] == 0 || map[r][c - 2] == 3)   //箱子前面 map[r-2][c]是否为空地或目的地
				{
					map[r][c - 2] += 4;       //箱子向上移动
					map[r][c - 1] += 1;       //人移动到原箱子位置
					map[r][c] -= 5;           //原先的人位置变为空地0
				}
			}

			break;
		case VK_RIGHT:
		case'd':         //右
		case'D':
		case 77:
			if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
			{
				map[r][c + 1] += 5;    //人向上移动
				map[r][c] -= 5;        //原位置变回空地0 
			}
			else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
			{
				if (map[r][c + 2] == 0 || map[r][c + 2] == 3)   //箱子前面 map[r-2][c]是否为空地或目的地
				{
					map[r][c + 2] += 4;       //箱子向上移动
					map[r][c + 1] += 1;       //人移动到原箱子位置
					map[r][c] -= 5;           //原先的人位置变为空地0
				}
			}
			//if (map[r][c + 1] == 0)
			//{
			//	map[r][c + 1] += 5;    //人向上移动
			//	map[r][c] -= 5;        //原位置变回空地0 
			//}
			//else if (map[r][c + 1] == 3)        //人5的前面是目的地
			//{
			//	map[r][c + 1] += 8;
			//	map[r][c] -= 5;
			//}
			break;
		}
		return 0;
	}
 //int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	//MessageBox(NULL, L"恭喜你赢啦 !", L"提示", 0);
	//return 0;
//}
	