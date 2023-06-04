#pragma once
#include "Header.h"
#include "Character.h"

class Wall : public Character
{
public:
	Wall();
	void draw();
	void print();
private:

};
Wall::Wall()
{
	symbol = "■";
	color = "\033[33m";
}
void Wall::print()
{
	cout << color << symbol << "\033[0m";
}
void Wall::draw() {
	if (currentMap != nullptr)
	{
		currentMap->draw();
	}
}