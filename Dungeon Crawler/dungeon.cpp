#include "dungeon.h"
#include "item.cpp"
#include "npc.h"
#include "door.cpp"
#include <random>
#include <iostream> //TODO: remove after testing rando

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
	
	item sword;
	sword.name = "Big Sword";
	sword.damage = 25;
	sword.type = 2;
	rooms[3][2].items.push_back(sword);

	NPC trader = NPC("Trader", 300, 50);
	rooms[2][0].npcs.push_back(trader);

	item key;
	key.name = "Merchant's key";
	key.type = 3;
	rooms[2][0].items.push_back(key);

	GameCharacter bat = GameCharacter("Bat", 20, 5);
	GameCharacter boss = GameCharacter("Ghoul", 250, 15);
	Door exit;
	item healthFlask;
	healthFlask.name = "Potion";
	healthFlask.health = 30;
	healthFlask.type = 1;
	healthFlask.uses = 0;
	healthFlask.maxUses = 2;
	healthFlask.isConsumable = true;
	
	// List of stuff for a dungeon floor to include
	// player, door, merchant & key
	// healthFlask, sword, enemies
	
	int maxEnemies = 5;
	int numEnemies = 0;
	int numBosses = 0;
	int numFlasks = 0;
	int numDoors = 0;
	
	std::random_device rando;
	std::mt19937 gen(rando());
	std::uniform_int_distribution<> distrib(0, 15);
	
	while (maxEnemies != numEnemies)
	{
	for (auto i = 0; i < rows; ++i)
	{
		for (auto j = 0; j < cols; ++j)
		{
			if (distrib(gen) == 1 && maxEnemies != numEnemies)
			{
				rooms[i][j].enemies.push_back(bat);
				++numEnemies;
				std::cout << "bat at :" << i << j << std::endl;
			}
			else if (distrib(gen) == 2 && numBosses < 1)
			{
				rooms[i][j].enemies.push_back(boss);
				++numBosses;
				std::cout << "boss at :" << i << j << std::endl;
			}
			else if (distrib(gen) == 3 && numFlasks < 2)
			{
				rooms[i][j].items.push_back(healthFlask);
				++numFlasks;
				std::cout << "flask at :" << i << j << std::endl;
			} else if (distrib(gen) == 4 && numDoors < 1)
			{
				rooms[i][j].doors.push_back(exit);
				++numDoors;
				std::cout << "exit door at :" << i << j << std::endl;
			}
		}
	}
	}
	// end of test while
}
