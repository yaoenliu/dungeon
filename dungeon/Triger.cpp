/***********************************************************************
 * File: Triger.cpp
 * Author: 劉耀恩
 * Create Date: 2023/06/06
 * Editor: 劉耀恩
 * Update Date: 2023/06/06
 * Description: Triger class
***********************************************************************/
#include "Header.h"
#include "Triger.h"

Triger::Triger()
{

}
void Triger::setSymbol(string symbol)
{
	this->symbol = symbol;
}
int Triger::getX()
{
	return this->x;
}
int Triger::getY()
{
	return this->y;
}
void Triger::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Triger::setPos(Position p)
{
	this->x = p.x;
	this->y = p.y;
}
Position Triger::getPos()
{
	Position p;
	p.x = this->x;
	p.y = this->y;
	return p;
}
string Triger::getSymbol()
{
	return this->symbol;
}




