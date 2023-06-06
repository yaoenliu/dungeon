/***********************************************************************
 * File: Character.cpp
 * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
 * Description: Character class
***********************************************************************/
#include "Map.h"
#include "Character.h"
#include <iostream>
using namespace std;
void Character::setPos(Position p, Map* m) {
	position = p;
	currentMap = m;
}
void Character::setPos(int x, int y, Map* m) {
	position.x = x;
	position.y = y;
	currentMap = m;
	m->characterIn(this);
}
string Character::getSymbol() {
	return symbol;
}
Position Character::getPos() {
	return position;
}

void Character::move(int x, int y) {
	if (currentMap != nullptr)
	{
		int reply = currentMap->moveRequest(position.x + x, position.y + y);
		if (reply == 1)
		{
			currentMap->characterOut(this);
			position.x += x;
			position.y += y;
			currentMap->characterIn(this);
		}
		if (reply == -1 && x == -1)
		{
			currentMap->characterOut(this);
			currentMap = currentMap->getLeft();
			position.x = currentMap->getWidth() - 2;
			position.y = currentMap->getRightTrail();
			currentMap->characterIn(this);
		}
		if (reply == -1 && x == 1)
		{
			currentMap->characterOut(this);
			currentMap = currentMap->getRight();
			position.x = 1;
			position.y = currentMap->getLeftTrail();
			currentMap->characterIn(this);
		}
		if (reply == -1 && y == -1)
		{
			currentMap->characterOut(this);
			currentMap = currentMap->getTop();
			position.x = currentMap->getBottomTrail();
			position.y = currentMap->getHeight() - 2;
			currentMap->characterIn(this);
		}
		if (reply == -1 && y == 1)
		{
			currentMap->characterOut(this);
			currentMap = currentMap->getBottom();
			position.x = currentMap->getTopTrail();
			position.y = 1;
			currentMap->characterIn(this);
		}
	}
}
void Character::print() {
	cout <<color<< symbol<< "\033[0m";
}



