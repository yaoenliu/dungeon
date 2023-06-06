/***********************************************************************
 * File: Hero.h
 * Author: 劉耀恩
 * Create Date: 2023/06/06
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
 * Description: Hero class
***********************************************************************/
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
	int getHp();
	int getExp();
	int getLevel();
	void setHp(int hp);
	void setExp(int exp);
	void setLevel(int level);

private:
	int hp = 100;
	int exp =0;
	int level=1;
};
