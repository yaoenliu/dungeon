/***********************************************************************
 * File: Map.h
  * Author: 劉耀恩
 * Create Date: 2023/04/28
 * Editor: 劉耀恩
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include "Header.h"
#include "Map.h"
#include "Triger.h"
#include "Enemy.h"

class Map
{
private:
	// Map layout
	Character*** layout = nullptr;
	// Map size
	int width;
	int height;
	// Link to other maps
	int topTrail = -1;
	int bottomTrail = -1;
	int leftTrail = -1;
	int rightTrail = -1;
	Map* top = nullptr;
	Map* bottom = nullptr;
	Map* left = nullptr;
	Map* right = nullptr;
public:
	Map();
	Map(int, int);
	void draw();
	void setTop(Map*, int);
	void setBottom(Map*, int);
	void setLeft(Map*, int);
	void setRight(Map*, int);
	Map* getTop();
	Map* getBottom();
	Map* getLeft();
	Map* getRight();
	int getTopTrail();
	int getBottomTrail();
	int getLeftTrail();
	int getRightTrail();
	int getWidth();
	int getHeight();
	int moveRequest(int, int);
	int inRequest(int, int);
	void characterIn(Character*);
	void characterOut(Character*);
	void InitializeMap();
	void maze();
	void save(std::string, vector<Triger*> heal, vector<Triger*> exp, vector<Enemy*> enemy, vector<Enemy*> enemy2, HeroSta sta);
	HeroSta load(std::string, vector<Triger*>& heal, vector<Triger*>& exp, vector<Enemy*>& enemy, vector<Enemy*>& enemy2);
};