/***********************************************************************
 * File: Character.h
 * Author: ¼BÄ£®¦
 * Create Date: 2023/04/28
 * Editor: ¼BÄ£®¦
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#pragma once
#include "Header.h"
#include "Position.h"
using namespace std;
class Character
{
public:
	// Setters
	void setPos(Position pos, Map* m);
	void setPos(int x, int y, Map* m);
	// Getters
	Position getPos();
	char getSymbol();
	Map* getCurrentMap();
	void move(int, int);
	// Functions
	void print();
protected:
	Map* currentMap = nullptr;
	Position position = { 1,1 };
	char symbol = '@';
	string color = "\033[31m";
};
