/***********************************************************************
 * File: Map.cpp
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/04/28
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: Map class
***********************************************************************/
#include "Character.h"
#include "Map.h"
#include "maze.h"
#include "Triger.h"
#include "Enemy.h"
#include <iostream>
#include<fstream>

#define Mapwallmode 1 // set to 1 if the map size includes the walls

using namespace std;

//intent: constructor
//pre:
//post:
Map::Map()
{

}

//intent: constructor
//pre: width and height of the map
//post:
Map::Map(int w, int h) {
	width = w;
	height = h;
	InitializeMap();
}

//intent: draw the map
//pre:
//post:
void Map::draw() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (layout[i][j] != nullptr)
				layout[i][j]->print();
			else
				cout << " ";
		}
		cout << endl;
	}
}

//intent: set the top wall of the map
//pre: a map and a int
//post:
void Map::setTop(Map* m, int t)
{
	top = m;
	topTrail = t;
}

//intent: set the bottom wall of the map
//pre: a map and a int
//post:
void Map::setBottom(Map* m, int t)
{
	bottom = m;
	bottomTrail = t;
}

//intent: set the left wall of the map
//pre: a map and a int
//post:
void Map::setLeft(Map* m, int t)
{
	left = m;
	leftTrail = t;
}

//intent: set the right wall of the map
//pre: a map and a int
//post:
void Map::setRight(Map* m, int t)
{
	right = m;
	rightTrail = t;
}

//intent: get the top wall of the map
//pre:
//post: return the top wall of the map
Map* Map::getTop()
{
	return top;
}

//intent: get the bottom wall of the map
//pre:
//post: return the bottom wall of the map
Map* Map::getBottom()
{
	return bottom;
}

//intent: get the left wall of the map
//pre:
//post: return the left wall of the map
Map* Map::getLeft()
{
	return left;
}

//intent: get the right wall of the map
//pre:
//post: return the right wall of the map
Map* Map::getRight()
{
	return right;
}

//intent: check if the move is valid
//pre: x and y of the move
//post: return 0 if the move is invalid
int Map::moveRequest(int x, int y)
{
	// Return 0 if the move is invalid
	// Return 1 if the move is valid
	// Return -1 if the move is valid and the player has moved to a new map
	if (x == 0 && y == leftTrail)
	{
		return -1;
	}
	if (x == width - 1 && y == rightTrail)
	{
		return -1;
	}
	if (y == 0 && x == topTrail)
	{
		return -1;
	}
	if (y == height - 1 && x == bottomTrail)
	{
		return -1;
	}
	if (x < 0 + Mapwallmode || x >= width - Mapwallmode || y < 0 + Mapwallmode || y >= height - Mapwallmode)
		return 0;
	if (layout[y][x] != nullptr)
		if (layout[y][x]->getSymbol() == "\u2588")
			return 0;
	return 1;
}

//intent: check if the move is valid
//pre: x and y of the move
//post: return 0 if the move is invalid
int Map::inRequest(int x, int y)
{
	if (x < 0 + Mapwallmode || x >= width - Mapwallmode || y < 0 + Mapwallmode || y >= height - Mapwallmode)
		return false;
	else if (layout[y][x] == nullptr)
		return true;
	else
		return false;

}

//intent: layout the character on the map
//pre: a character
//post:
void Map::characterIn(Character* c)
{
	layout[c->getPos().y][c->getPos().x] = c;
}

//intent: remove the character from the map
//pre: a character
//post:
void Map::characterOut(Character* c)
{
	layout[c->getPos().y][c->getPos().x] = nullptr;
}

//intent: initialize the map
//pre:
//post:
void Map::InitializeMap()
{
	// Initialize the map
	layout = new Character * *[height];
	for (int i = 0; i < height; i++)
	{
		layout[i] = new Character * [width];
		for (int j = 0; j < width; j++)
		{
			layout[i][j] = nullptr;
		}
	}
}

//intent: get the top trail of the map
//pre:
//post: return the top trail of the map
int Map::getTopTrail()
{
	return topTrail;
}

//intent: get the bottom trail of the map
//pre:
//post: return the bottom trail of the map
int Map::getBottomTrail()
{
	return bottomTrail;
}

//intent: get the left trail of the map
//pre:
//post: return the left trail of the map
int Map::getLeftTrail()
{
	return leftTrail;
}

//intent: get the right trail of the map
//pre:
//post: return the right trail of the map
int Map::getRightTrail()
{
	return rightTrail;
}

//intent: get the width of the map
//pre:
//post: return the width of the map
int Map::getWidth()
{
	return width;
}

//intent: get the height of the map
//pre:
//post: return the height of the map
int Map::getHeight()
{
	return height;
}


//intent: generate a maze
//pre:
//post:
void Map::maze()
{
	int** board = new int* [height];
	for (int i = 0; i < height; i++)
		board[i] = new int[width];
	gen(board, height - 2, width - 2);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 2)
				layout[i][j] = nullptr;
			else
			{
				layout[i][j] = new Character();
			}				
		}
	}
}

//intent: save the map
//pre: file path, heal, exp, enemy, enemy2, hero status
//post:
void Map::save(string filePath, vector<Triger*> heal, vector<Triger*> exp, vector<Enemy*> enemy, vector<Enemy*> enemy2, HeroSta sta)
{
	system("mkdir save");
	ofstream file;
	file.open(filePath);
	file << width << " " << height << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			if (layout[i][j] == nullptr)
				file << "0";
			else if (layout[i][j]->getSymbol() == "\u2588")
				file << "1";
			else if (layout[i][j]->getSymbol() == "H")
				file << layout[i][j]->getSymbol();
			else
				file << "0";
		}
		file << endl;
	}
	while (!heal.empty())
	{
		file << "+ " << heal.back()->getPos().x << " " << heal.back()->getPos().y << endl;
		heal.pop_back();
	}
	while (!exp.empty())
	{
		file << "T " << exp.back()->getPos().x << " " << exp.back()->getPos().y << endl;
		exp.pop_back();
	}
	while (!enemy.empty())
	{
		file << "E" << enemy.back()->getPos().x << " " << enemy.back()->getPos().y << endl;
		enemy.pop_back();
	}
	while (!enemy2.empty())
	{
		file << "X" << enemy2.back()->getPos().x << " " << enemy2.back()->getPos().y << endl;
		enemy2.pop_back();
	}
	file << "R" << sta.hp << " " << sta.exp << " " << sta.level << endl;
	file.close();
}

//intent: load the map
//pre: file path, heal, exp, enemy, enemy2
//post: return the hero status
HeroSta Map::load(string filePath, vector<Triger*>& heal, vector<Triger*>& exp, vector<Enemy*>& enemy, vector<Enemy*>& enemy2)
{
	ifstream file;
	file.open(filePath);
	file >> width >> height;
	InitializeMap();
	char c;
	Position p = { 0,0 };
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			file >> c;
			if (c == '0')
				layout[i][j] = nullptr;
			else if (c == '1')
				layout[i][j] = new Character();
			else if (c == 'H')
			{
				p.x = j;
				p.y = i;
			}
		}
	}
	while (file >> c)
	{
		int x;
		int y;

		if (c == '+')
		{
			file >> x >> y;
			Triger* t = new Triger();
			t->setPos(x, y);
			t->setSymbol("\033[32m+\033[0m");
			heal.push_back(t);
		}
		else if (c == 'T')
		{
			file >> x >> y;
			Triger* t = new Triger();
			t->setPos(x, y);
			t->setSymbol("\033[36mT\033[0m");
			exp.push_back(t);
		}
		else if (c == 'E')
		{
			file >> x >> y;
			Enemy* e = new Enemy();
			e->setPos(x, y, this);
			e->setSymbol("\033[31mE\033[0m");
			enemy.push_back(e);
		}
		else if (c == 'X')
		{
			file >> x >> y;
			Enemy* e = new Enemy();
			e->setPos(x, y, this);
			e->setSymbol("\033[31mX\033[0m");
			enemy2.push_back(e);
		}
		else
			break;
	}
	int staHP;
	int staEXP;
	int staLevel;
	file >> staHP >> staEXP >> staLevel;
	HeroSta s = { p, staHP, staEXP, staLevel };
	file.close();
	return s;
}

