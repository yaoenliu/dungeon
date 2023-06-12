/***********************************************************************
 * File: Hero.cpp
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/06/06
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: Hero class
***********************************************************************/
#include "Hero.h"
#include "Map.h"

//intent: constructor
//pre:
//post:
Hero::Hero()
{
	symbol = "H";
	color = "\033[33m";
}

//intent: print the hero
//pre:	
//post:
void Hero::print()
{
	cout << color << symbol << "\033[0m";
}

//intent: draw the hero
//pre:
//post:
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

//intent: got exp
//pre: an int
//post:
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

//intent: got hp
//pre: an int
//post:
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

//intent: get the hp
//pre:
//post: return the hp
int Hero::getHp()
{
	return hp;
}

//intent: get the exp
//pre:
//post: return the exp
int Hero::getExp()
{
	return exp;
}

//intent: get the level
//pre:
//post: return the level
int Hero::getLevel()
{
	return level;
}

//intent: set the hp
//pre: an int
//post:
void Hero::setHp(int hp)
{
	this->hp = hp;
}

//intent: set the exp
//pre: an int
//post:
void Hero::setExp(int exp)
{
	this->exp = exp;
}

//intent: set the level
//pre: an int
//post:
void Hero::setLevel(int level)
{
	this->level = level;
}
