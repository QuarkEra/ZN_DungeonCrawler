#include "room.cpp"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
public:
	const int rows = 4;
	const int cols = 4;
	room rooms[4][4];

	void createDungeon();
};

#endif
