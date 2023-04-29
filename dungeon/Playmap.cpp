#include "Playmap.h"
#include "Character.h"
#include <iostream>
using namespace std;
Map::Map(int w, int h) {
	width = w;
	height = h;
	layout = new Character**[height];
	for (int i = 0; i < height; i++)
	{
		layout[i] = new Character*[width];
		for (int j = 0; j < width; j++)
		{
			layout[i][j] = nullptr;
		}
	}
}
Map::Map(int w, int h, char wa, char f) :width(w), height(h), wall(wa), floor(f) {
	layout = new Character**[height];
	for (int i = 0; i < height; i++)
	{
		layout[i] = new Character*[width];
		for (int j = 0; j < width; j++)
		{
			layout[i][j] = nullptr;
		}
	}
}
void Map::draw() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 && topTrail != j)
				cout << wall;
			else if (i == height - 1 && bottomTrail != j)
				cout << wall;
			else if (j == 0 && leftTrail != i)
				cout << wall;
			else if (j == width - 1 && rightTrail != i)
				cout << wall;
			else if (layout[i][j] != nullptr)
				cout << layout[i][j]->getSymbol();
			else
				cout << floor;
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
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false;
	if (layout[y][x] != nullptr)
		return false;
	return true;
}
void Map::characterIn(Character& c)
{
	layout[c.getPos().y][c.getPos().x] = &c;
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
