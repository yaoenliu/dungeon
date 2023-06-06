#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	void setSymbol(string symbol) { this->symbol = symbol; }
};
