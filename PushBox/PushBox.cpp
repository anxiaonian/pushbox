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
		{ 0,1,1,1,1,1,1,0 },  //0��ʾ�յ�
		{ 0,1,0,0,0,0,1,1 },  //1��ǽ
		{ 1,1,3,1,1,4,0,1 },  //3��Ŀ�ĵ�
		{ 1,0,3,3,4,0,0,1 },  //4������
		{ 1,0,0,1,4,0,0,1 },  //5����
		{ 1,0,0,5,0,1,1,1 },
		{ 1,1,1,1,1,1,0,0 }
	};

	void Game();
	void draw(IMAGE img[], int map[][CPol]);       //,int map[][CPol +2]
	int Move(int map[][CPol]);

	//������
	int main() {
	
		//mciSendString(L"")
		PlaySound((LPCTSTR)IDR_WAVE1, 0, SND_RESOURCE | SND_ASYNC);
		while (1) {
			system("cls");
			Game();
		/*	if (MessageBox(hWnd, L"��һ��?", L"�˳�", MB_RETRYCANCEL) == IDCANCEL) {
				break ;
			}*/
		}
		//closegraph;
		return 0;
	}
	//��������
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
	//				printf("��");
	//				break;
	//			case 3:
	//				printf("��");
	//				break;
	//			case 4:
	//				printf("��");
	//				break;
	//			case 5:
	//				printf("��");
	//				break;
	//			case 7:
	//				printf("��");   //���Ӻ�Ŀ�ĵ�
	//				break;
	//			case 8:
	//				printf("��");    //�˺�Ŀ�ĵ�
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
		
      //������670*680//  512, 448
		initgraph(512,448);
     //����ͼƬ
		IMAGE img[5];

		//�ӵ�ǰ��Ŀ�ļ���Ŀ¼�¼���ͼƬ
	/*	loadimage(&img[0], L"00.jpg", 64, 64);
		loadimage(&img[1], L"01.jpg",64, 64);
		loadimage(&img[2], L"03.jpg", 64, 64);
		loadimage(&img[3], L"04.jpg",64, 64);
		loadimage(&img[4], _T("05.jpg"), 64, 64);*/

		//����Դ�ļ�����ͼƬ
		loadimage(&img[0], L"JPG", MAKEINTRESOURCE(100), 64, 64);
		loadimage(&img[1], L"JPG", MAKEINTRESOURCE(101), 64, 64);
		loadimage(&img[2], L"JPG", MAKEINTRESOURCE(103), 64, 64);
		loadimage(&img[3], L"JPG", MAKEINTRESOURCE(104), 64, 64);
		loadimage(&img[4], _T("JPG"),MAKEINTRESOURCE(105), 64, 64);
	
		win = 0;
		//��ͼ����
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
			MessageBox(hWnd, L"��Ӯ��", L"��Ϣ����", MB_OK);
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
							//	printf("��");
								break;
								
							case 3:	putimage(64 * j , 64 * i, &img[2]);
							//	printf("��");
								break;
							
							case 4:	putimage(64 * j, 64 * i, &img[3]);
							//	printf("��");
								break;
							
							case 5: putimage(64 * j , 64 * i, &img[4]);
								//printf("��");
								break;
								
							case 7:	putimage(64 * j, 64 * i, &img[3]);
								//printf("��");   //���Ӻ�Ŀ�ĵ�
								break;

							case 8:	putimage(64 * j, 64 * i, &img[4]);
								//printf("��");    //�˺�Ŀ�ĵ�
								break;
								default:
								break;
							}
						}
						//printf("\n");
					}
				}
			

	
	//�ƶ�
	int Move(int map[][CPol]) {
		char ch;
		int i, j;
		int r, c;       //�˵�����
		ch = _getch();   //�����<conio.h>ͷ�ļ�,ֱ�ӽ����ַ�,���ð��س�
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
			if (map[i][j] == 5 || map[i][j] == 8)  //�ж�����Ŀ�ĵ�
				break;
		}

		switch (ch)
		{
		case VK_UP:
		case'w':         //��
		case'W':
		case 72:        //��ֵ
						//�˵����� map[r][c], ����һ��λ�� map[r-1][c] �Ƿ�Ϊ�յ�0��Ŀ�ĵ�3,�Ǿͽ���ֵ
			if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
			{
				map[r - 1][c] += 5;    //�������ƶ�
				map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			}
			else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
			{
				if (map[r - 2][c] == 0 || map[r - 2][c] == 3)   //����ǰ�� map[r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
				{
					map[r - 2][c] += 4;       //���������ƶ�
					map[r - 1][c] += 1;       //���ƶ���ԭ����λ��
					map[r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
			
				}
			}


			//	if (map[r - 1][c] == 0)
			//	{
			//		map[r - 1][c] += 5;    //�������ƶ�
			//		map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			//}
			//	else if (map[r - 1][c] == 3)        //��5��ǰ����Ŀ�ĵ�
			//	{
			//		map[r - 1][c] += 8;   
			//		map[r][c] -= 5;
			//	}
			break;

		case VK_DOWN:
		case's':         //��
		case'S':
		case 80:
			if (map[r + 1][c] == 0 || map[r + 1][c] == 3)
			{
				map[r + 1][c] += 5;    //�������ƶ�
				map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			}
			else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
			{
				if (map[r + 2][c] == 0 || map[r + 2][c] == 3)   //����ǰ�� map[r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
				{
					map[r + 2][c] += 4;       //���������ƶ�
					map[r + 1][c] += 1;       //���ƶ���ԭ����λ��
					map[r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
				}
			}

			break;

		case VK_LEFT:
		case'a':         //��
		case'A':
		case 75:
			if (map[r][c - 1] == 0 || map[r][c - 1] == 3)
			{
				map[r][c - 1] += 5;    //�������ƶ�
				map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			}
			else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
			{
				if (map[r][c - 2] == 0 || map[r][c - 2] == 3)   //����ǰ�� map[r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
				{
					map[r][c - 2] += 4;       //���������ƶ�
					map[r][c - 1] += 1;       //���ƶ���ԭ����λ��
					map[r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
				}
			}

			break;
		case VK_RIGHT:
		case'd':         //��
		case'D':
		case 77:
			if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
			{
				map[r][c + 1] += 5;    //�������ƶ�
				map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			}
			else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
			{
				if (map[r][c + 2] == 0 || map[r][c + 2] == 3)   //����ǰ�� map[r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
				{
					map[r][c + 2] += 4;       //���������ƶ�
					map[r][c + 1] += 1;       //���ƶ���ԭ����λ��
					map[r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
				}
			}
			//if (map[r][c + 1] == 0)
			//{
			//	map[r][c + 1] += 5;    //�������ƶ�
			//	map[r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
			//}
			//else if (map[r][c + 1] == 3)        //��5��ǰ����Ŀ�ĵ�
			//{
			//	map[r][c + 1] += 8;
			//	map[r][c] -= 5;
			//}
			break;
		}
		return 0;
	}
 //int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	//MessageBox(NULL, L"��ϲ��Ӯ�� !", L"��ʾ", 0);
	//return 0;
//}
	