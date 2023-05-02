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
void setCursorPosition(int, int);

// global variable
Map* currentMap = nullptr;
bool keyState[256] = { false };
bool keyPress = false;

int  main()
{
	clearConsoleScreen();
	Map map(30, 20, '#', ' ');
	Map map2(20, 25, '#', ' ');
	Map map3(30, 25, '#', ' ');
	map.setLeft(&map2, 10);
	map2.setRight(&map, 15);
	map.setTop(&map3, 10);
	map3.setBottom(&map, 20);
	currentMap = &map;
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
			setCursorPosition(hero.getPos().x, hero.getPos().y);
			cout << " ";
			if (keyState['w'] == true)
				hero.move(0, -1);
			else if (keyState['s'] == true)
				hero.move(0, 1);
			else if (keyState['a'] == true)
				hero.move(-1, 0);
			else if (keyState['d'] == true)
				hero.move(1, 0);
			if (hero.getCurrentMap() != currentMap)
			{
				clearConsoleScreen();
				hero.draw();
				currentMap = hero.getCurrentMap();
				setCursorPosition(0, 0);
			}
			else
			{
				setCursorPosition(hero.getPos().x, hero.getPos().y);
				hero.print();
				setCursorPosition(0, 0);
			}			
			keyPress = false;
		}
	}
	clearConsoleScreen();
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
void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
	// https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
}