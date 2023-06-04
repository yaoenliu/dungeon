/***********************************************************************
 * File: Map.cpp
 * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#include "Character.h"
#include "Map.h"
#include "maze.h"
#include <iostream>
#define Mapwallmode 0 // set to 1 if the map size includes the walls

using namespace std;
Map::Map(int w, int h) {
	width = w;
	height = h;
	InitializeMap();
}
void Map::draw() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (layout[i][j] != nullptr)
				layout[i][j]->print();
			else
				cout <<" ";
		}
		cout << endl;
	}
}
void Map::setTop(Map* m, int t)
{
	top = m;
	topTrail = t;
}
void Map::setBottom(Map* m, int t)
{
	bottom = m;
	bottomTrail = t;
}
void Map::setLeft(Map* m, int t)
{
	left = m;
	leftTrail = t;
}
void Map::setRight(Map* m, int t)
{
	right = m;
	rightTrail = t;
}
Map* Map::getTop()
{
	return top;
}
Map* Map::getBottom()
{
	return bottom;
}
Map* Map::getLeft()
{
	return left;
}
Map* Map::getRight()
{
	return right;
}
// Return 0 if the move is invalid
// Return 1 if the move is valid
// Return -1 if the move is valid and the player has moved to a new map
int Map::moveRequest(int x, int y)
{
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
		return 0;
	return 1;
}
void Map::characterIn(Character* c)
{
	layout[c->getPos().y][c->getPos().x] = c;
}
void Map::characterOut(Character* c)
{
	layout[c->getPos().y][c->getPos().x] = nullptr;
}
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
int Map::getTopTrail()
{
	return topTrail;
}
int Map::getBottomTrail()
{
	return bottomTrail;
}
int Map::getLeftTrail()
{
	return leftTrail;
}
int Map::getRightTrail()
{
	return rightTrail;
}
int Map::getWidth()
{
	return width;
}
int Map::getHeight()
{
	return height;
}

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
				layout[i][j] = new Character();
		}
	}
}

