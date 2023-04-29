#pragma once
#include "Header.h"
#include "Character.h"

class Hero : public Character
{
public:
	Hero();
	void draw();
	void print();
private:

};
Hero::Hero()
{
	symbol = 'H';
	color = "\033[33m";
}
void Hero::print()
{
	cout <<color << symbol << "\033[0m";
}
void Hero::draw() {
	if (currentMap != nullptr)
	{
		currentMap->draw();
	}
}