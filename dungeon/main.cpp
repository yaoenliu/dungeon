/***********************************************************************
 * File: main.cpp
 * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/04/29
 * Description: main function
***********************************************************************/
// stander C/C++ library
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include<Windows.h>
#include<vector>
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
void ListDirectoryContents(vector<string>&);
int menuDraw(string* menu, int length);
int menuDraw(vector<string> menu);
// global variable
Map* currentMap = nullptr;
bool keyState[256] = { false };
bool keyPress = false;

int  main()
{
	string gamefile;
	string menu[3] = { "new game","load game","exit" };
	int menuIndex = 0;
	while (1)
	{
		clearConsoleScreen();
		for (int i = 0; i < 3; i++)
		{
			if (i == menuIndex)
				cout << "[■]";
			else
				cout << "[ ]";
			cout << menu[i] << endl;
		}
		char c = _getch();
		if (c == 'w' && menuIndex > 0)
			menuIndex--;
		if (c == 's' && menuIndex < 2)
			menuIndex++;
		if (c == '\r')
		{
			if (menuIndex == 0)
			{
				string level[3] = { "level1","level2","level3" };
				string * levelPtr = level;
				int levelIndex = menuDraw(levelPtr, 3);
				if (levelIndex == -1)
					continue;
				else
				{
					gamefile = level[levelIndex];
					break;
				}					
			}
			else if (menuIndex == 1)
			{
				vector<string> saveList;
				ListDirectoryContents(saveList);
				int saveIndex = menuDraw(saveList);
				if (saveIndex == -1)
					continue;
				else
				{
					gamefile = saveList[saveIndex];
					break;
				}
			}
			else if (menuIndex == 2)
			{
				return 0;
			}
		}
	}
	Hero hero;
	if (gamefile == "level1")
	{
		Map * map = new Map(11, 11);
		currentMap = map;
		map->maze();
		hero.setPos (1,1,currentMap);
		clearConsoleScreen();
		hero.draw();
	}
	if (gamefile == "level2")
	{
		Map* map = new Map(21, 21);
		currentMap = map;
		map->maze();
		hero.setPos(1, 1, currentMap);
		clearConsoleScreen();
		hero.draw();
	}
	if (gamefile == "level3")
	{
		Map* map = new Map(31, 31);
		currentMap = map;
		map->maze();
		hero.setPos(1, 1, currentMap);
		clearConsoleScreen();
		hero.draw();
	}
	else
	{

	}
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
			hero.draw();
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

void ListDirectoryContents(vector<string>& saveList)
{
	saveList.clear ();
	WIN32_FIND_DATAA fileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::string searchPath = "./save/*.sav";
	hFind = FindFirstFileA(searchPath.c_str(), &fileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			saveList.push_back(fileData.cFileName);
		} while (FindNextFileA(hFind, &fileData) != 0);
		FindClose(hFind);
	}
}

int menuDraw(string* menu, int length)
{
	int menuIndex = -1;
	while (true)
	{
		clearConsoleScreen();
		for (int i = -1; i < length; i++)
		{
			if (i == menuIndex)
				cout << "[■]";
			else
				cout << "[ ]";
			if(i!=-1)
				cout << menu[i] << endl;
			else 
				cout << "Back" << endl;
		}
		char c = _getch();
		if (c == 'w' && menuIndex > -1)
			menuIndex--;
		if (c == 's' && menuIndex < length - 1)
			menuIndex++;
		if (c == '\r')
		{
			return menuIndex;
		}
	}
}
int menuDraw(vector<string> menu)
{
	int menuIndex = -1;
	int length = menu.size();
	while (true)
	{
		clearConsoleScreen();
		for (int i = -1; i < length; i++)
		{
			if (i == menuIndex)
				cout << "[■]";
			else
				cout << "[ ]";
			if (i != -1)
				cout << menu[i] << endl;
			else
				cout << "Back" << endl;
		}
		char c = _getch();
		if (c == 'w' && menuIndex > -1)
			menuIndex--;
		if (c == 's' && menuIndex < length-1)
			menuIndex++;
		if (c == '\r')
		{
			return menuIndex;
		}
	}
}
