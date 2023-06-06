#pragma once
#include <iostream>
using namespace std;
class Triger
{
public:
	Triger();
	void setPos(int x, int y);
	void setPos(Position p);
	int getX();
	int getY();
	void setSymbol(string symbol);
	Position getPos();
	string getSymbol();
private:
	int x;
	int y;
	string symbol;
};
