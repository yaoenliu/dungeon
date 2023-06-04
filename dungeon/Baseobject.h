#pragma once
#include "Header.h"
#include "Position.h"
using namespace std;
class Baseobject
{
public:
	// Setters
	void setPos(Position pos, Map* m);
	void setPos(int x, int y, Map* m);
	// Getters
	Position getPos();
	virtual char getSymbol();
	Map* getCurrentMap();
	// Functions
	virtual void print();
protected:
	Map* currentMap = nullptr;
	Position position = { 1,1 };
	char symbol = ' '; // default symbol
	string color = "\033[0m"; // default color
};
