#include "Baseobject.h"
#include "Map.h"
#include <iostream>
using namespace std;
void Baseobject::setPos(Position p, Map* m) {
	position = p;
	currentMap = m;
}
void Baseobject::setPos(int x, int y, Map* m) {
	position.x = x;
	position.y = y;
	currentMap = m;
	m->characterIn(this);
}
char Baseobject::getSymbol() {
	return symbol;
}
Position Baseobject::getPos() {
	return position;
}
void Baseobject::print() {
	cout << color << symbol << "\033[0m";
}
Map* Baseobject::getCurrentMap()
{
	return currentMap;
}

