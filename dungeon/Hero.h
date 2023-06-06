
#pragma once
#include "Header.h"
#include "Character.h"
class Hero : public Character
{
public:
	Hero();
	void draw();
	void print();
	void gotExp(int exp);
	void gotHp(int hp);
	int getHp() { return hp; }
	int getExp() { return exp; }
	int getLevel() { return level; }
	void setHp (int hp) { this->hp = hp; }
	void setExp(int exp) { this->exp = exp; }
	void setLevel(int level) { this->level = level; }

private:
	int hp = 100;
	int exp =0;
	int level=1;
};
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
