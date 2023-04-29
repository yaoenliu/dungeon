/***********************************************************************
 * File: Ccs.h
 * Author: �Bģ��
 * Create Date: 2023/04/27
 * Editor: �Bģ��
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#pragma once
#ifndef _CCS_H_
#define _CCS_H_
#include<Windows.h>
void clearConsoleScreen()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hStdOut, ' ', cellCount, coord, &count);
	FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);
	SetConsoleCursorPosition(hStdOut, coord);
}
#endif