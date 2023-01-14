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
	GameCharacter skeleton = GameCharacter("Skeleton", 100, 5);
	GameCharacter ghoul = GameCharacter("Ghoul", 250, 10);
	rooms[1][0].enemies.push_back(bat);
	rooms[0][0].enemies.push_back(ghoul);
	rooms[0][1].enemies.push_back(skeleton);

	item healthFlask;
	healthFlask.name = "Potion";
	healthFlask.health = 30;
	healthFlask.uses = 0;
	healthFlask.maxUses = 2;
	healthFlask.isConsumable = true;
	rooms[0][2].items.push_back(healthFlask);

	item sword;
	sword.name = "Master Sword";
	sword.damage = 25;
	sword.type = 2;
	rooms[2][1].items.push_back(sword);

	NPC trader = NPC("Trader", 300, 50);
	rooms[2][0].npcs.push_back(trader);
}
