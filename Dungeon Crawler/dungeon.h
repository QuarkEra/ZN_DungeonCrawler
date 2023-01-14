#include "room.cpp"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
public:
	const int rows = 3;
	const int cols = 3;
	room rooms[3][3];

	void createDungeon();
};

#endif
