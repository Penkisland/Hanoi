/* 班级 学号 姓名 */
#include<iostream>
#include"cmd_console_tools.h"
#include"hanoi.h"
#include<Windows.h>
#include<iomanip>
#include<conio.h>

int count = 0;
int a[10]{}, b[10]{}, c[10]{};
int atop = 0, btop = 0, ctop = 0;
/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：
***************************************************************************/
void pause(int t)
{
	switch (t)
	{
		case 0:
			while (true)
			{
				if (_getch() == 0x0D)
				{
					break;
				}
			}
			break;
		case 1:
			Sleep(100);
			break;
		case 2:
			Sleep(500);
			break;
		case 3:
			Sleep(250);
			break;
		case 4:
			Sleep(100);
			break;
		case 5:
			Sleep(1);
			break;
	}
}

void getOrder(char* src, char* tmp, char* dst)
{
	cct_setcolor();
	while (true)
	{
		cct_gotoxy(0, 34);
		std::cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：    \b\b";
		std::cin >> *src;
		if ((*src == 'q' || *src == 'Q'))
		{
			cct_gotoxy(0, 35);
			std::cout << "游戏中止！";
			break;
		}
		std::cin >> *dst;
		std::cin.ignore(1024, '\n');
		if ((*dst == 'q' || *dst == 'Q'))
		{
			cct_gotoxy(0, 35);
			std::cout << "游戏中止！";
			break;
		}
		if ((*src < 'd' && *src >= 'a') || (*src < 'D' && *src >= 'A'))
		{
			if ((*dst < 'd' && *dst >= 'a') || (*dst < 'D' && *dst >= 'A'))
			{
				if (*src > 'C')
				{
					*src -= 'a' - 'A';
				}
				if (*dst > 'C')
				{
					*dst -= 'a' - 'A';
				}
				if (*src != *dst)
					break;
			}
		}
	}
	if (*src == 'A')
	{
		if (*dst == 'B')
			*tmp = 'C';
		else
			*tmp = 'B';
	}
	else if (*src == 'B')
	{
		if (*dst == 'A')
			*tmp = 'C';
		else
			*tmp = 'A';
	}
	else
	{
		if (*dst == 'A')
			*tmp = 'B';
		else
			*tmp = 'A';
	}
}

int* getSrc(char src)
{
	if (src == 'A')
		return a;
	else if (src == 'B')
		return b;
	else
		return c;
}

int* getTmp(char tmp)
{
	if (tmp == 'A')
		return a;
	else if (tmp == 'B')
		return b;
	else
		return c;
}

int* getDst(char dst)
{
	if (dst == 'A')
		return a;
	else if (dst == 'B')
		return b;
	else
		return c;
}

void init()
{
	atop = 0;
	btop = 0;
	ctop = 0;
	for (int i = 0; i < 10; i++)
	{
		a[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		b[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		c[i] = 0;
	}
}

void movePlates(char src, char dst, int plates, int time)
{
	int* s = getSrc(src);
	int* d = getDst(dst);
	int sx, dx;
	int* stop, * dtop;
	{
		if (src == 'A')
			sx = 13;
		else if (src == 'B')
			sx = 43;
		else
			sx = 73;
		if (dst == 'A')
			dx = 13;
		else if (dst == 'B')
			dx = 43;
		else
			dx = 73;
		if (s == a)
			stop = &atop;
		else if (s == b)
			stop = &btop;
		else
			stop = &ctop;
		if (d == a)
			dtop = &atop;
		else if (d == b)
			dtop = &btop;
		else
			dtop = &ctop;
	}
	for (int j = 14 - *stop; j > 0; j--)
	{
		Sleep(25);
		cct_showch(sx - plates + *stop - 1, j + 1, ' ', COLOR_BLACK, plates - *stop + 5, 2 * (plates + 2 - *stop));
		if (j > 1)
			cct_showstr(sx, j + 1, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 1);
		cct_showstr(sx - plates + *stop - 1, j, "\u2588", COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
	}//move up
	if (sx > dx)
	{
		for (int i = sx - plates + *stop - 1; i > dx - plates + *stop - 2; i--)
		{
			Sleep(25);
			cct_showch(i + 1, 1, ' ', COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
			cct_showstr(i, 1, "\u2588", COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
		}
	}
	else
	{
		for (int i = sx - plates + *stop - 1; i < dx - plates + *stop; i++)
		{
			Sleep(25);
			cct_showch(i - 1, 1, ' ', COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
			cct_showstr(i, 1, "\u2588", COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
		}
	}
	for (int j = 1; j < 15 - *dtop; j++)
	{
		Sleep(25);
		if (j > 1)
			cct_showch(dx - plates + *stop - 2, j - 1, ' ', COLOR_BLACK, plates - *stop + 5, 2 * (plates + 2 - *stop));
		if (j > 3)
			cct_showstr(dx, j - 1, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 1);
		cct_showstr(dx - plates + *stop - 1, j, "\u2588", COLOR_BLACK, plates - *stop + 5, plates + 2 - *stop);
	}
}

void printRods()
{
	cct_showstr(1, 15, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 13);
	cct_showstr(31, 15, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 13);
	cct_showstr(61, 15, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 13);
	for (int i = 0; i < 12; i++)
	{
		cct_showstr(13, 14 - i, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 1);
		Sleep(50);
		cct_showstr(43, 14 - i, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 1);
		Sleep(50);
		cct_showstr(73, 14 - i, "\u2588", COLOR_BLACK, COLOR_HYELLOW, 1);
		Sleep(50);
	}
}

void printPlates(int plates)
{
	for (int i = 0; i < atop; i++)
	{
		cct_showstr(13 - plates + i, 14 - i, "\u2588", COLOR_BLACK, plates - i + 4, plates + 1 - i);
	}
	for (int i = 0; i < btop; i++)
	{
		cct_showstr(43 - plates + i, 14 - i, "\u2588", COLOR_BLACK, plates - i + 4, plates + 1 - i);
	}
	for (int i = 0; i < ctop; i++)
	{
		cct_showstr(73 - plates + i, 14 - i, "\u2588", COLOR_BLACK, plates - i + 4, plates + 1 - i);
	}
}

void inputTime(int* t)
{
	while (true)
	{
		std::cout << "请输入移动速度(0 - 5：0 - 按回车单步演示 1 - 延时最长 5 - 延时最短) ";
		std::cin >> *t;
		if (std::cin.good() == 0)
		{
			std::cin.clear();
			std::cin.ignore(1024, '\n');
		}
		else if (0 <= *t && *t <= 5)
		{
			break;
		}
	}
}

void hanoiInput(int* plate, char* src, char* dst, char* tmp)
{
	while (true)
	{
		std::cout << "请输入汉诺塔的层数(1-10)：\n";
		std::cin >> *plate;
		if (std::cin.good() == 0)
		{
			std::cin.clear();
			std::cin.ignore(1024, '\n');
		}
		else if (*plate < 11 && *plate>0)
		{
			break;
		}
	}
	while (true)
	{
		std::cout << "请输入起始柱(A-C)：\n";
		std::cin >> *src;
		if ((*src < 'd' && *src >= 'a') || (*src < 'D' && *src >= 'A'))
		{
			if (*src > 'C')
			{
				*src -= 'a' - 'A';
			}
			break;
		}
	}
	while (true)
	{
		std::cout << "请输入目标柱(A-C)：\n";
		std::cin >> *dst;
		if ((*dst < 'd' && *dst >= 'a') || (*dst < 'D' && *dst >= 'A'))
		{
			if (*dst > 'C')
			{
				*dst -= 'a' - 'A';
			}
			if (*dst != *src)
				break;
		}
	}
	if (*src == 'A')
	{
		if (*dst == 'B')
			*tmp = 'C';
		else
			*tmp = 'B';
	}
	else if (*src == 'B')
	{
		if (*dst == 'A')
			*tmp = 'C';
		else
			*tmp = 'A';
	}
	else
	{
		if (*dst == 'A')
			*tmp = 'B';
		else
			*tmp = 'A';
	}
}

void srcRodsInit(char src, int plates)
{
	if (src == 'A')
	{
		for (int i = 0; i < plates; i++)
		{
			a[i] = plates - i;
		}
		atop = plates;
	}
	else if (src == 'B')
	{
		for (int i = 0; i < plates; i++)
		{
			b[i] = plates - i;
		}
		btop = plates;
	}
	else
	{
		for (int i = 0; i < plates; i++)
		{
			c[i] = plates - i;
		}
		ctop = plates;
	}
}

void popAndPush(int* src, int* dst)
{
	int* stop;
	int* dtop;
	if (src == a)
		stop = &atop;
	else if (src == b)
		stop = &btop;
	else
		stop = &ctop;
	if (dst == a)
		dtop = &atop;
	else if (dst == b)
		dtop = &btop;
	else
		dtop = &ctop;
	dst[(*dtop)++] = src[--(*stop)];
	src[*stop] = 0;
}

void printState(int plate)
{
	std::cout << "A: ";
	for (int i = 0; i < 10; i++)
	{
		if (a[i] != 0)
			std::cout << std::setw(2) << a[i] << ' ';
		else
			std::cout << std::setw(2) << ' ' << ' ';
	}
	std::cout << std::setw(5) << ' ';
	std::cout << "B: ";
	for (int i = 0; i < 10; i++)
	{
		if (b[i] != 0)
			std::cout << std::setw(2) << b[i] << ' ';
		else
			std::cout << std::setw(2) << ' ' << ' ';
	}
	std::cout << std::setw(5) << ' ';
	std::cout << "C: ";
	for (int i = 0; i < 10; i++)
	{
		if (c[i] != 0)
			std::cout << std::setw(2) << c[i] << ' ';
		else
			std::cout << std::setw(2) << ' ' << ' ';
	}
	std::cout << std::setw(5) << ' ' << std::endl;
}

void printVertical(int opt)
{
	if (opt == 4)
	{
		cct_showch(9, 12, '=', COLOR_BLACK, COLOR_WHITE, 25);
		cct_showstr(9, 13, "  A         B         C", COLOR_BLACK, COLOR_WHITE, 1, -1);
		for (int i = 0; i < 10; i++)
		{
			if (a[i] != 0)
			{
				cct_gotoxy(10, 11 - i);
				std::cout << std::setw(2) << a[i];
			}
			else
			{
				cct_gotoxy(10, 11 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (b[i] != 0)
			{
				cct_gotoxy(20, 11 - i);
				std::cout << std::setw(2) << b[i];
			}
			else
			{
				cct_gotoxy(20, 11 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (c[i] != 0)
			{
				cct_gotoxy(30, 11 - i);
				std::cout << std::setw(2) << c[i];
			}
			else
			{
				cct_gotoxy(30, 11 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
	}
	else
	{
		cct_showch(9, 30, '=', COLOR_BLACK, COLOR_WHITE, 25);
		cct_showstr(9, 31, "  A         B         C", COLOR_BLACK, COLOR_WHITE, 1, -1);
		for (int i = 0; i < 10; i++)
		{
			if (a[i] != 0)
			{
				cct_gotoxy(10, 29 - i);
				std::cout << std::setw(2) << a[i];
			}
			else
			{
				cct_gotoxy(10, 29 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (b[i] != 0)
			{
				cct_gotoxy(20, 29 - i);
				std::cout << std::setw(2) << b[i];
			}
			else
			{
				cct_gotoxy(20, 29 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (c[i] != 0)
			{
				cct_gotoxy(30, 29 - i);
				std::cout << std::setw(2) << c[i];
			}
			else
			{
				cct_gotoxy(30, 29 - i);
				std::cout << std::setw(2) << ' ';
			}
		}
	}
}

void hanoiInText(char src, char tmp, char dst, int plate)
{
	if (plate == 1)
	{
		std::cout << plate << '#' << ' ' << src << "---->" << dst << std::endl;
		return;
	}
	hanoiInText(src, dst, tmp, plate - 1);
	std::cout << plate << '#' << ' ' << src << "---->" << dst << std::endl;
	hanoiInText(tmp, src, dst, plate - 1);
}

void hanoiRecordSteps(char src, char tmp, char dst, int plate)
{
	if (plate == 1)
	{
		count++;
		std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
		return;
	}
	hanoiRecordSteps(src, dst, tmp, plate - 1);
	count++;
	std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
	hanoiRecordSteps(tmp, src, dst, plate - 1);
}

void hanoiInnerArray_yoko(char src, char tmp, char dst, int plate)
{
	if (plate == 1)
	{
		count++;
		popAndPush(getSrc(src), getDst(dst));
		std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
		printState(plate);
		return;
	}
	hanoiInnerArray_yoko(src, dst, tmp, plate - 1);
	count++;
	popAndPush(getSrc(src), getDst(dst));
	std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
	printState(plate);
	hanoiInnerArray_yoko(tmp, src, dst, plate - 1);
}

void hanoiInnerArray_vertical(char src, char tmp, char dst, int plate, int time)
{
	if (plate == 1)
	{
		count++;
		popAndPush(getSrc(src), getDst(dst));
		cct_gotoxy(0, 17);
		pause(time);
		cct_setcursor(CURSOR_INVISIBLE);
		std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
		printState(plate);
		printVertical(4);
		return;
	}
	hanoiInnerArray_vertical(src, dst, tmp, plate - 1, time);
	count++;
	popAndPush(getSrc(src), getDst(dst));
	cct_gotoxy(0, 17);
	pause(time);
	cct_setcursor(CURSOR_INVISIBLE);
	std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
	printState(plate);
	printVertical(4);
	hanoiInnerArray_vertical(tmp, src, dst, plate - 1, time);
}

int getTop(char rod)
{
	int top = 0;
	if (rod == 'A')
	{
		top = atop - 1;
	}
	else if (rod == 'B')
	{
		top = btop - 1;
	}
	else
	{
		top = ctop - 1;
	}
	return top;
}

void hanoiVisible(char src, char tmp, char dst, int plate, int time)
{
	if (plate == 1)
	{
		count++;
		pause(time);
		movePlates(src, dst, plate + getTop(src), time);
		popAndPush(getSrc(src), getDst(dst));
		cct_setcursor(CURSOR_INVISIBLE);
		cct_gotoxy(0, 18);
		cct_setcolor();
		std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
		printState(plate);
		printVertical(8);
		return;
	}
	hanoiVisible(src, dst, tmp, plate - 1, time);
	count++;
	pause(time);
	movePlates(src, dst, plate + getTop(src), time);
	popAndPush(getSrc(src), getDst(dst));
	cct_setcursor(CURSOR_INVISIBLE);
	cct_gotoxy(0, 18);
	cct_setcolor();
	std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
	printState(plate);
	printVertical(8);
	hanoiVisible(tmp, src, dst, plate - 1, time);
}

void multipleSolutions(char opt)
{
	int plate = 0;
	int time = 0;
	count = 0;
	char src = '\0', tmp = '\0', dst = '\0';
	init();
	switch (opt)
	{
		case '0':
			exit(0);
			break;
		case '1':
			cct_gotoxy(0, 14);
			hanoiInput(&plate, &src, &dst, &tmp);
			hanoiInText(src, tmp, dst, plate);
			break;
		case '2':
			cct_gotoxy(0, 14);
			hanoiInput(&plate, &src, &dst, &tmp);
			hanoiRecordSteps(src, tmp, dst, plate);
			break;
		case '3':
			cct_gotoxy(0, 14);
			hanoiInput(&plate, &src, &dst, &tmp);
			srcRodsInit(src, plate);
			hanoiInnerArray_yoko(src, tmp, dst, plate);
			break;
		case '4':
			cct_gotoxy(0, 14);
			hanoiInput(&plate, &src, &dst, &tmp);
			srcRodsInit(src, plate);
			inputTime(&time);
			cct_cls();
			std::cout << "从 " << src << " 移动到 " << dst << "，共 " << plate << " 层，延时设置为 " << time;
			hanoiInnerArray_vertical(src, tmp, dst, plate, time);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cct_gotoxy(0, 38);
			break;
		case '5':
			cct_cls();
			printRods();
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cct_gotoxy(0, 38);
			break;
		case '6':
			cct_cls();
			hanoiInput(&plate, &src, &dst, &tmp);
			srcRodsInit(src, plate);
			cct_cls();
			printRods();
			printPlates(plate);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cct_gotoxy(0, 38);
			break;
		case '7':
			cct_cls();
			hanoiInput(&plate, &src, &dst, &tmp);
			srcRodsInit(src, plate);
			cct_cls();
			printRods();
			printPlates(plate);
			movePlates(src, dst, plate, time);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cct_gotoxy(0, 38);
			break;
		case '8':
			cct_cls();
			hanoiInput(&plate, &src, &dst, &tmp);
			inputTime(&time);
			srcRodsInit(src, plate);
			cct_cls();
			std::cout << "从 " << src << " 移动到 " << dst << "，共 " << plate << " 层，延时设置为 " << time;
			printRods();
			printPlates(plate);
			hanoiVisible(src, tmp, dst, plate, time);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cct_gotoxy(0, 38);
			break;
		case '9':
			cct_cls();
			hanoiInput(&plate, &src, &dst, &tmp);
			srcRodsInit(src, plate);
			cct_cls();
			std::cout << "从 " << src << " 移动到 " << dst << "，共 " << plate << " 层";
			printRods();
			printPlates(plate);
			while (getTop(dst) < plate)
			{
				getOrder(&src, &tmp, &dst);
				if (src == 'q' || src == 'Q' || dst == 'q' || dst == 'Q')
					break;
				while (true)
				{
					cct_showch(0, 35, ' ', 0, 7, 34);
					if (((getSrc(src)[getTop(src)] < getDst(dst)[getTop(dst)]) || getDst(dst)[getTop(dst)] == 0) && getSrc(src)[getTop(src)] != 0)
					{
						count++;
						movePlates(src, dst, getSrc(src)[0], 0);
						popAndPush(getSrc(src), getDst(dst));
						cct_gotoxy(0, 18);
						cct_setcolor();
						std::cout << "第" << std::setw(4) << count << " 步(" << std::setw(2) << plate << '#' << ' ' << src << "---->" << dst << ")" << std::endl;
						printState(plate);
						printVertical(9);
						break;
					}
					if (getSrc(src)[getTop(src)] > getDst(dst)[getTop(dst)])
					{
						cct_gotoxy(0, 35);
						std::cout << "非法移动，大盘压小盘！";
						break;
					}
					if (getSrc(src)[getTop(src)] == 0)
					{
						cct_gotoxy(0, 35);
						std::cout << "非法移动，起始柱为空！";
						break;
					}
				}
			}
			cct_gotoxy(0, 38);
			break;
		default:
			break;
	}
}