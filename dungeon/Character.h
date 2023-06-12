/***********************************************************************
 * File: Character.h
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/04/28
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: Character class
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
	string getSymbol();
	void move(int, int);
	// Functions
	void print();
protected:
	Map* currentMap = nullptr;
	Position position = { 1,1 };
	string  symbol = "\u2588";
	string color = "\033[0m";
};
