#include "dungeon.h"
#include "player.h"
#include <chrono>
#include <thread>
#include "vector"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
	Dungeon* dungeon;
	Player* player;

public:
	bool isGameOver;
	Game(Player*, Dungeon*);

	void handleEnemyActions();
	void engageCombat();
	void handleItemActions();

	std::vector<std::string> getMovementActions();
	void handleMovement();
	void printMovementActions(std::vector<std::string>);
	void printItemActions(std::vector<std::string>);
	void printFightActions(std::vector<std::string>);
	void initiateRooms();
};

#endif