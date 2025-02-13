#ifndef __DIRECTION_H
#define __DIRECTION_H
struct Direction {
	int x, y;
	bool operator==(const Direction& other) const {
		return x == other.x && y == other.y;
	}
	Direction operator-() const { return Direction{ -x, y };}
};
#endif