#include "game.h"
#include <iostream>

Game::Game(Player* _player, Dungeon* _dungeon)
{
	player = _player;
	dungeon = _dungeon;
	isGameOver = false;
	dungeon->createDungeon();
	player->currentRoom = &dungeon->rooms[dungeon->rows - 1][dungeon->cols - 1];
}

void Game::initiateRooms()
{
	room* room = player->currentRoom;

	if (room->row == 0 && room->col == 0 && room->enemies.empty())
	{
		std::cout << "Congratulations! Now you are the strongest monster in the dungeon, " << player->getName() << "!" << std::endl;
		isGameOver = true;
	}
	if (!player->currentRoom->enemies.empty())
	{
		handleEnemyActions();
	}
	else if (!player->currentRoom->items.empty())
	{
		handleItemActions();
	}
	else
	{
		handleMovement();
	}
}

void Game::handleEnemyActions()
{
	std::cout << "An enemy " << player->currentRoom->enemies[0].getName() << " is here!" << std::endl;
	std::vector<std::string> actions;

	actions.push_back("Engage");
	actions.push_back("Retreat");
	printActions(actions);

	int input;
	std::cin >> input;
	if (input == 1)
	{
		engageCombat();
	}
	else
	{
		player->retreat();
	}
}

void Game::engageCombat()
{
	GameCharacter* enemy = &player->currentRoom->enemies[0];
	while (true)
	{
		room* room = player->currentRoom;
		
		enemy->recieveDamage(player->getDamage());
		std::cout << "You hit " << enemy->getName() << " for " << player->getDamage() << " points of damage!\n";
		if (!enemy->isAlive())
		{
			puts("You are victorious!");
			player->currentRoom->enemies.clear();		
			return;
		}

		player->recieveDamage(enemy->getDamage());
		std::cout << "You are injured by " << enemy->getName() << " for " << enemy->getDamage() << " points of damage! \n";
		std::cout << "You now have " << player->getHealth() << "HP left." << std::endl;
		if (!player->isAlive())
		{
			isGameOver = true;
			puts("Valiant effort!");
			return;
		}

		puts("Keep fighting or run away?");
		std::vector<std::string> actions;
		actions.push_back("Fight!");
		actions.push_back("Retreat!");
		printActions(actions);
		int input;
		std::cin >> input;
		if (input == 2)
		{
			player->retreat();
			return;
		}
	}
}

void Game::handleItemActions()
{
	item item = player->currentRoom->items[0];
	std::cout << "You found a " << item.name << "!" << std::endl;
	std::vector<std::string> actions;
	actions.push_back("Pick it up");
	actions.push_back("Leave it");
	printActions(actions);

	int input;
	std::cin >> input;
	if (input == 1)
	{
		player->pickUpItem(item);
		std::cout << "Your HP is " << player->getHealth() << " and damage is now " << player->getDamage() << "." << std::endl;
		player->currentRoom->items.clear();
	}
	else
	{
		handleMovement();
	}
}

std::vector<std::string> Game::getMovementActions()
{
	std::vector<std::string> actions;

	room* currentRoom = player->currentRoom;
	if (currentRoom->col > 0)
	{
		actions.push_back("West");
	}
	if (currentRoom->row > 0)
	{
		actions.push_back("North");
	}
	if (currentRoom->col < (dungeon->cols - 1))
	{
		actions.push_back("East");
	}
	if (currentRoom->row < (dungeon->rows - 1))
	{
		actions.push_back("South");
	}

	return actions;
}

void Game::printActions(std::vector<std::string> actions)
{
	for (int i = 0; i < signed(actions.size()); i++)
	{
		std::cout << i + 1 << ". " << actions[i] << std::endl;
	}
}

void Game::handleMovement()
{
	std::vector<std::string> actions = getMovementActions();
	printActions(actions);
	int input;
	std::cin >> input;
	std::string chosenAction = actions[input - 1];
	
	int horzMove = 0;
	int vertMove = 0;
	if (chosenAction == "West")
	{
		horzMove = -1;
	}	else if (chosenAction == "East")
	{
		horzMove = 1;
	}	else if (chosenAction == "North")
	{
		vertMove = -1;
	}	else if (chosenAction == "South")
	{
		vertMove = 1;
	}

	room* newRoom = &dungeon->rooms[player->currentRoom->row + vertMove][player->currentRoom->col + horzMove];
	player->moveToRoom(newRoom);
}