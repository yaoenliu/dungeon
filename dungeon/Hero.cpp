/***********************************************************************
 * File: Hero.cpp
 * Author: 劉耀恩
 * Create Date: 2023/06/06
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
 * Description: Hero class
***********************************************************************/
#include "Hero.h"
#include "Map.h"
Hero::Hero()
{
	symbol = "H";
	color = "\033[33m";
}
void Hero::print()
{
	cout << color << symbol << "\033[0m";
}
void Hero::draw() {
	if (currentMap != nullptr)
	{
		currentMap->draw();
		cout << "HP: " << getHp() << endl;
		cout << "EXP: " << getExp() << endl;
		cout << "LV: " << getLevel() << endl;
		cout << "Press 'w' to go up, 's' to go down, 'a' to go left, 'd' to go right, 'esc' to quit" << endl;
		cout << "Press m to save the game" << endl; 
	}
}
void Hero::gotExp(int exp)
{
	this->exp += exp;
	while (this->exp >= 100)
	{
		this->exp -= 100;
		level++;
		hp = 100;
	}
}
void Hero::gotHp(int hp)
{
	this->hp += hp;
	if (this->hp <= 0)
	{
		this->hp = 0;
	}
	else if (this->hp >= 100)
	{
		this->hp = 100;
	}
}
int Hero::getHp()
{
	return hp;
}
int Hero::getExp()
{
	return exp;
}
int Hero::getLevel()
{
	return level;
}
void Hero::setHp(int hp)
{
	this->hp = hp;
}
void Hero::setExp(int exp)
{
	this->exp = exp;
}
void Hero::setLevel(int level)
{
	this->level = level;
}
