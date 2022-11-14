#include "dungeon.h"
#include "player.h"
#include <chrono>
#include <thread>
#include "vector"
#include "npc.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
	Dungeon* dungeon;
	Player* player;
	NPC* trader;

public:
	bool isGameOver;
	Game(Player*, Dungeon*, NPC*);

	void handleEnemyActions();
	void engageCombat();
	void handleItemActions();
	void handleTrader();

	std::vector<std::string> getMovementActions();
	void handleMovement();
	void printMovementActions(std::vector<std::string>);
	void printItemActions(std::vector<std::string>);
	void printFightActions(std::vector<std::string>);
	void printTraderActions(std::vector<std::string>);
	void initiateRooms();
};

#endif