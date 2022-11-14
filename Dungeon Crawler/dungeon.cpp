#include "dungeon.h"
#include "item.cpp"
#include "npc.h"

void Dungeon::createDungeon()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			room room;
			room.row = i;
			room.col = j;
			rooms[i][j] = room;
		}
	}

	GameCharacter bat = GameCharacter("Bat", 80, 5);
	GameCharacter skeleton = GameCharacter("Skeleton", 130, 5);
	GameCharacter ghoul = GameCharacter("Ghoul", 215, 10);

	rooms[2][1].enemies.push_back(bat);
	rooms[1][0].enemies.push_back(bat);
	rooms[0][0].enemies.push_back(ghoul);
	rooms[0][1].enemies.push_back(skeleton);

	item greenHerb;
	greenHerb.health = 25;
	greenHerb.name = "Green Herb";
	greenHerb.type = 1;

	rooms[1][1].items.push_back(greenHerb);
	rooms[1][0].items.push_back(greenHerb);

	item sword;
	sword.name = "Master Sword";
	sword.damage = 15;
	sword.type = 2;

	rooms[0][2].items.push_back(sword);

	NPC trader = NPC("Trader", 300, 50);
	rooms[2][0].npcs.push_back(trader);
}