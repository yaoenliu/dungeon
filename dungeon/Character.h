/***********************************************************************
 * File: Character.h
 * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#pragma once
#include "Header.h"
#include "Position.h"
#include "Baseobject.h"
using namespace std;
class Character : public Baseobject
{
public:
	void move(int, int);
	virtual void print();
protected:
};
