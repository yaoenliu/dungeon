/***********************************************************************
 * File: Enemy.h
 * Author: 劉耀恩
 * Create Date: 2023/06/06
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
 * Description: Enemy class
***********************************************************************/
#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	void setSymbol(string symbol);
};
