/***********************************************************************
 * File: main.cpp
 * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
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
#include  "Triger.h"
#include "HeroSta.h"
#include "Enemy.h"

// global namespace
using namespace std;
// function prototype
void clearConsoleScreen();
void keyUpdate();
void ListDirectoryContents(vector<string>&);
void setCursorPosition(int x, int y);
void save(Hero hero);
void healT(int n);
void expT(int n);
void eneV(int);
void eneV2(int);
void updateScreen();
int menuDraw(string* menu, int length);
int menuDraw(vector<string> menu);
// global variable
Map* currentMap = nullptr;
bool keyState[256] = { false };
bool keyPress = false;
vector <Triger*> trigerList;
vector <Triger*> healList;
vector <Enemy*> enemyList;
vector <Enemy*> enemy2List;
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
				string* levelPtr = level;
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
		currentMap = new Map(11, 11);
		currentMap->maze();
		hero.setPos(1, 1, currentMap);
		expT(2);
		healT(2);
		eneV(2);
		eneV2(2);
	}
	else if (gamefile == "level2")
	{
		currentMap = new Map(21, 21);
		currentMap->maze();
		hero.setPos(1, 1, currentMap);
		expT(4);
		healT(4);
		eneV(4);
		eneV2(4);
	}
	else if (gamefile == "level3")
	{
		currentMap = new Map(31, 31);
		currentMap->maze();
		hero.setPos(1, 1, currentMap);
		expT(8);
		healT(8);
		eneV(8);
		eneV2(8);
	}
	else
	{
		currentMap = new Map();
		HeroSta hStatus = currentMap->load("./save/" + gamefile, healList, trigerList, enemyList, enemy2List);
		hero.setPos(hStatus.pos, currentMap);
		hero.setExp( hStatus.exp);
		hero.setHp(hStatus.hp);
		hero.setLevel(hStatus.level);
	}
	Timer timer(1);
	timer.start();
	clearConsoleScreen();
	hero.draw();
	updateScreen();
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
			if (keyState['m'] == true)
				save(hero);

			for (int i = 0; i < trigerList.size(); i++)
				if (hero.getPos().x == trigerList[i]->getPos().x && hero.getPos().y == trigerList[i]->getPos().y)
					hero.gotExp(10);
			for (int i = 0; i < healList.size(); i++)
				if (hero.getPos().x == healList[i]->getPos().x && hero.getPos().y == trigerList[i]->getPos().y)
					hero.gotHp(10);
			for (int i = 0; i < enemyList.size(); i++)
			{
				if (hero.getPos().x == enemyList[i]->getPos().x && hero.getPos().y == enemyList[i]->getPos().y)
				{
					hero.gotHp(-40);
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
				}
			}
			for (int i = 0; i < enemy2List.size(); i++)
			{
				if (hero.getPos().x == enemy2List[i]->getPos().x && hero.getPos().y == enemy2List[i]->getPos().y)
				{
					hero.gotHp(-10);
					delete enemy2List[i];
					enemy2List.erase(enemy2List.begin() + i);
					eneV2(1);					
				}
			}
			for (int i = 0; i < enemyList.size(); i++)
			{
				int x = rand() % 3 - 1;
				int y = rand() % 3 - 1;
				enemyList[i]->move(x, y);
			}
			clearConsoleScreen();
			hero.draw();
			updateScreen();
			keyPress = false;
			if (hero.getHp() <= 0)
			{
				cout << "You died" << endl;
				return 886;
			}
			if (hero.getLevel() >= 10)
			{
				cout << "You win" << endl;
				return 777;
			}
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
	saveList.clear();
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
			if (i != -1)
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
		if (c == 's' && menuIndex < length - 1)
			menuIndex++;
		if (c == '\r')
		{
			return menuIndex;
		}
	}
}
void save(Hero hero)
{
	clearConsoleScreen();
	cout << "Enter save name: ";
	string saveName;
	cin >> saveName;
	HeroSta heroSta = { hero.getPos(), hero.getHp(), hero.getExp(), hero.getLevel() };
	currentMap->save("./save/" + saveName + ".sav", healList, trigerList, enemyList, enemy2List, heroSta);
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
	// https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
}

void healT(int n)
{
	for (int i = 0; i < n; i++)
	{
		Triger* triger = new Triger();
		int max = currentMap->getWidth();
		int x = 0;
		int y = 0;
		while (!currentMap->inRequest(x, y))
		{
			x = rand() % max;
			y = rand() % max;
		}
		triger->setPos(x, y);
		triger->setSymbol("\033[32m+\033[0m");
		healList.push_back(triger);
	}
}

void expT(int n)
{
	for (int i = 0; i < n; i++)
	{
		Triger* triger = new Triger();
		int max = currentMap->getWidth();
		int x = 0;
		int y = 0;
		while (!currentMap->inRequest(x, y))
		{
			x = rand() % max;
			y = rand() % max;
		}
		triger->setPos(x, y);
		triger->setSymbol("\033[36mT\033[0m");
		trigerList.push_back(triger);
	}
}

void eneV(int n)
{
	for (int i = 0; i < n; i++)
	{
		Enemy * enemy = new Enemy();
		int max = currentMap->getWidth();
		int x = 0;
		int y = 0;
		while (!currentMap->moveRequest(x, y))
		{
			x = rand() % max;
			y = rand() % max;
		}
		enemy->setPos (x, y , currentMap);
		enemy->setSymbol("\033[31mE\033[0m");
		enemyList.push_back(enemy);
	}
}
void eneV2(int n)
{
	for (int i = 0; i < n; i++)
	{
		Enemy* enemy = new Enemy();
		int max = currentMap->getWidth();
		int x = 0;
		int y = 0;
		while (!currentMap->moveRequest(x, y))
		{
			x = rand() % max;
			y = rand() % max;
		}
		enemy->setPos(x, y, currentMap);
		enemy->setSymbol("\033[31mX\033[0m");
		enemy2List.push_back(enemy);
	}
}

void updateScreen ()
{
	for (int i = 0; i < trigerList.size(); i++)
	{
		setCursorPosition(trigerList[i]->getX(), trigerList[i]->getY());
		cout << trigerList[i]->getSymbol();
	}
	for (int i = 0; i < healList.size(); i++)
	{
		setCursorPosition(healList[i]->getX(), trigerList[i]->getY());
		cout << healList[i]->getSymbol();
	}
	setCursorPosition(0, 5 + currentMap->getHeight());
}
