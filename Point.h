#ifndef __POINT_H
#define __POINT_H
#include <iostream>
#include "Utils.h"
#include "GameConfig.h"

class Board;

class Point
{
	static constexpr int INIT_X = 0;
	static constexpr int INIT_Y = 0;
public:
	int x;
	int y;

	Point() : Point(INIT_X, INIT_Y) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Point& other) const { return x != other.x || y != other.y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
};

#endif