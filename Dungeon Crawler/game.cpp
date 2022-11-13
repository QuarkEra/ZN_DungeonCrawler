#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game(Player* _player, Dungeon* _dungeon)
{
	player = _player;
	dungeon = _dungeon;
	isGameOver = false;
	dungeon->createDungeon();
	player->currentRoom = &dungeon->rooms[dungeon->rows - 1][dungeon->cols - 1];
}

void Game::handleEnemyActions()
{
	std::cout << "An enemy " << player->currentRoom->enemies[0].getName() << " is here!" << std::endl;
	std::vector<std::string> fightActions;

	fightActions.push_back("(F)ight");
	fightActions.push_back("(r)etreat");
	printFightActions(fightActions);

	std::string input;
	std::getline(std::cin, input);
	if (input == "retreat" || input == "r")
	{
		player->retreat();
		return;
	}
	else if (input == "fight" || input == "f")
	{
		engageCombat();
	}
	else
	{
		puts("Please only enter valid responses indicated by brackets, 'f' in (F)ight for example.\n");
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

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		player->recieveDamage(enemy->getDamage());
		std::cout << enemy->getName() << " counters your attack for " << enemy->getDamage() << " points of damage! \n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "You now have " << player->getHealth() << "HP left." << std::endl;
		if (!player->isAlive())
		{
			isGameOver = true;
			puts("Valiant effort!");
			return;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		puts("Keep fighting or run away?");
		std::vector<std::string> actions;
		actions.push_back("(f)ight");
		actions.push_back("(r)etreat");
		printFightActions(actions);
		std::string input;
		std::getline(std::cin, input);
		if (input == "r")
		{
			player->retreat();
			return;
		}
		else if (input == "f")
		{
			continue;
		}
		else
		{
			puts("Please only enter valid responses indicated by brackets, 'f' in (F)ight for example.\n");
		}
	}
}

void Game::handleItemActions()
{
	item item = player->currentRoom->items[0];
	std::cout << "You found a " << item.name << "..." << std::endl;
	std::vector<std::string> itemActions;
	itemActions.push_back("(p)ick it up");
	itemActions.push_back("(l)eave it");
	printItemActions(itemActions);

	std::string input;
	std::getline(std::cin, input);
	if (input == "p")
	{
		player->pickUpItem(item);
		if (item.type == 1)
		{
			std::cout << "You feel refreshed, your HP increases to " << player->getHealth() << "." << std::endl;
		}
		else if (item.type == 2)
		{
			std::cout << "You feel stronger than ever, your damage has increased to " << player->getDamage() << "." << std::endl;
		}
		player->currentRoom->items.clear();
	}
	else if (input == "l")
	{
		handleMovement();
	}
	else
	{
		puts("Please only enter valid responses indicated by brackets, 'f' in (F)ight for example.\n");
	}
}

void Game::initiateRooms()
{
	room* room = player->currentRoom;

	if (room->row == 0 && room->col == 0 && room->enemies.empty())
	{
		std::cout << "Congratulations! Now you are the strongest monster in the dungeon, " << player->getName() << "!" << std::endl;
		puts("This thread will self-destruct in three seconds...");
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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
	else if (!isGameOver)
	{
		handleMovement();
	}
}

std::vector<std::string> Game::getMovementActions()
{
	std::vector<std::string> actions;

	room* currentRoom = player->currentRoom;
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
	if (currentRoom->col > 0)
	{
		actions.push_back("West");
	}
	return actions;
}

void Game::printMovementActions(std::vector<std::string> actions)
{
	for (int i = 0; i < actions.size(); i++)
	{
		std::cout << actions[i] << ", ";
	}
	puts("where will you go?");
}

void Game::printItemActions(std::vector<std::string> itemActions)
{
	for (size_t i = 0; i < itemActions.size(); i++)
	{
		std::cout << itemActions[i] << ", ";
	}
	puts("what will you do?");
}

void Game::printFightActions(std::vector<std::string> fightActions)
{
	for (size_t i = 0; i < fightActions.size(); i++)
	{
		std::cout << fightActions[i] << ", ";
	}
	puts("what will you do?");
}

void Game::handleMovement()
{
	std::vector<std::string> actions = getMovementActions();
	printMovementActions(actions);
	std::string input;
	std::getline(std::cin, input);
	
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	int horzMove = 0;
	int vertMove = 0;
	if (input == "west" || input == "w")
	{
		horzMove = -1;
	}	else if (input == "east" || input == "e")
	{
		horzMove = 1;
	}	else if (input == "north" || input == "n")
	{
		vertMove = -1;
	}	else if (input == "south" || input == "s")
	{
		vertMove = 1;
	}
	else
	{
		puts("Please only enter valid responses indicated by brackets, 'f' in (F)ight for example.\n");
	}

	room* newRoom = &dungeon->rooms[player->currentRoom->row + vertMove][player->currentRoom->col + horzMove];
	player->moveToRoom(newRoom);
}