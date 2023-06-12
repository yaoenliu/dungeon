/***********************************************************************
 * File: Triger.cpp
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/06/06
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: Triger class
***********************************************************************/
#include "Header.h"
#include "Triger.h"

//intent: constructor
//pre:
//post:
Triger::Triger()
{

}

//intent: set the symbol of the triger
//pre: a string
//post:
void Triger::setSymbol(string symbol)
{
	this->symbol = symbol;
}

//intent: get the x coordinate of the triger
//pre:	
//post: return the x coordinate of the triger
int Triger::getX()
{
	return this->x;
}

//intent: get the y coordinate of the triger
//pre:
//post: return the y coordinate of the triger
int Triger::getY()
{
	return this->y;
}

//intent: set the position of the triger
//pre: x and y coordinates
//post:
void Triger::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

//intent: set the position of the triger
//pre: a position
//post:
void Triger::setPos(Position p)
{
	this->x = p.x;
	this->y = p.y;
}

//intent: get the position of the triger
//pre:
//post: return the position of the triger
Position Triger::getPos()
{
	Position p;
	p.x = this->x;
	p.y = this->y;
	return p;
}

//intent: get the symbol of the triger
//pre:
//post: return the symbol of the triger
string Triger::getSymbol()
{
	return this->symbol;
}




