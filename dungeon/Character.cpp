/***********************************************************************
 * File: Character.cpp
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/04/28
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: Character class
***********************************************************************/
#include "Map.h"
#include "Character.h"
#include <iostream>

using namespace std;

//intent: set the position of the character
//pre: a position and a map
//post:
void Character::setPos(Position p, Map* m) {
	position = p;
	currentMap = m;
}

//intent: set the position of the character
//pre: x and y coordinates and a map
//post:
void Character::setPos(int x, int y, Map* m) {
	position.x = x;
	position.y = y;
	currentMap = m;
	m->characterIn(this);
}

//intent: get the symbol of the character
//pre:
//post: return the symbol of the character
string Character::getSymbol() {
	return symbol;
}

//intent: get the position of the character
//pre:
//post: return the position of the character
Position Character::getPos() {
	return position;
}

//intent: move the character
//pre: x and y coordinates
//post:
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

//intent: print the character
//pre:
//post:
void Character::print() {
	cout <<color<< symbol<< "\033[0m";
}



