#include <vector>
#include "gameCharacter.h"
#include "item.cpp"
#include "npc.h"

#ifndef ROOM_CPP
#define ROOM_CPP

struct room
{
	int row{};
	int col{};

	std::vector<GameCharacter> enemies;
	std::vector<item> items;
	std::vector<NPC> npcs;
};

#endif