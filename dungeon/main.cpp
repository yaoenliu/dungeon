/***********************************************************************
 * File: main.cpp
 * Author: ¼BÄ£®¦
 * Create Date: 2023/04/28
 * Editor: ¼BÄ£®¦
 * Update Date: 2023/04/29
 * Description: main function
***********************************************************************/
// stander C/C++ library
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include<Windows.h>

// user define library
#include "Map.h"
#include "Character.h"
#include "Position.h"
#include "Timer.h"
#include "Hero.h"

// global namespace
using namespace std;

// function prototype
void clearConsoleScreen();
void keyUpdate();

// global variable
Map* currentMap = nullptr;
bool keyState[256] = { false };
bool keyPress = false;

int  main()
{
	Map map(30, 20, '#', ' ');
	Map map2(20, 25, '#', ' ');
	Map map3(30, 25, '#', ' ');
	map.setLeft(&map2,10);
	map2.setRight(&map,15);
	map.setTop(&map3,10);
	map3.setBottom(&map,20);
	Hero hero;
	hero.setPos(10, 10, &map);
	Character monster;
	monster.setPos(15, 15, &map);
	map.draw();
	Timer timer(1);
	timer.start();
	while (keyState[27] == false)
	{
		if (timer.tick())
			keyUpdate();
		if (keyPress)
		{
			if (keyState['w'] == true)
				hero.move(0, -1);
			if (keyState['s'] == true)
				hero.move(0, 1);
			if (keyState['a'] == true)
				hero.move(-1, 0);
			if (keyState['d'] == true)
				hero.move(1, 0);
			clearConsoleScreen();
			hero .draw();
			keyPress = false;
		}
	}
}
void keyUpdate()
{
	if (_kbhit())
	{
		int key = _getch();
		keyState[key] = true;
		keyPress = true;
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			keyState[i] = false;
		}
	}
}
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