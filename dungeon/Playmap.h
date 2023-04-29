#pragma once
#include "Map.h"
#include "Character.h"
class Map : public Map
{
private:
	Character*** layout = nullptr;
	int width;
	int height;
	char wall = '#';
	char floor = ' ';
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
	Map(int, int);
	Map(int, int, char, char);
	void draw();
	void setTop(Playmap*, int);
	void setBottom(Playmap*, int);
	void setLeft(Playmap*, int);
	void setRight(Playmap*, int);
	Map* getTop();
	Map* getBottom();
	Map* getLeft();
	Map* getRight();
	int moveRequest(int, int);
	void characterIn(Character&);
	void InitializeMap();
};