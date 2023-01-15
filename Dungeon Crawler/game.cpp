#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game(Player* _player, Dungeon* _dungeon, NPC* _npc)
{
	player = _player;
	dungeon = _dungeon;
	trader = _npc;
	isGameOver = false;
	dungeon->createDungeon();
	
	player->currentRoom = &dungeon->rooms[dungeon->rows-1][dungeon->cols-1];
}

void Game::engageCombat()
{
	std::vector<item>::const_iterator c_iter; //for searching
	std::vector<item>::iterator iter; // for modifying
	
	GameCharacter* enemy = &player->currentRoom->enemies[0];
	std::cout << "A wild " << enemy->getName() << " attacks!" << std::endl;
	while (true)
	{
		std::vector<std::string> actions;
		if (!player->inventory.empty())
		{
			for (c_iter = player->inventory.begin(); c_iter != player->inventory.end(); ++c_iter)
			{
				if (c_iter->type == 1)
				{
					std::cout << "You have " << c_iter->name << " with " << (c_iter->maxUses - c_iter->uses) << " uses remaining." << std::endl;
					actions.push_back("(u)se potion");
					break;
				}
			}
		}
		actions.push_back("(f)ight");
		actions.push_back("(r)etreat");
		
		printActions(actions);
		std::string input;
		std::getline(std::cin, input);
		
		if (input == "r")
		{
			player->retreat();
			return;
		}
		else if (input == "f")
		{
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
		}
		else if (input == "u")
		{
			for (iter = player->inventory.begin(); iter != player->inventory.end(); ++iter) {
				if (iter->type == 1 && iter->maxUses != iter->uses) {
					++iter->uses;
					player->heal(iter->health);
					puts("You used the potion...");
					std::cout << "You have " << player->getHealth() << "HP." << std::endl;
					if (iter->uses == iter->maxUses) {
						player->inventory.erase(iter);
					}
				}
			}
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
	printActions(itemActions);

	std::string input;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	if (input == "p")
	{
		player->pickUpItem(item);
		if (item.type == 2)
		{
			std::cout << "You feel stronger than ever, your damage has increased to " << player->getDamage() << "." << std::endl;
		}
		else if (item.type == 3)
		{
			player->inventory.push_back(item);
		}
		else if (item.isConsumable)
		{
			player->inventory.push_back(item);
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

void Game::handleTrader()
{
	NPC npc = player->currentRoom->npcs[0];
	std::cout << "A ghastly figure emerges from the shadows and offers you a deal...\n you can trade half your current health and recieve a great gift of strength or lose half your strength and recover your health to it's maximum...\n you must make a choice to leave." << std::endl;
	std::vector<std::string> traderActions;
	traderActions.push_back("(h)ealth for damage");
	traderActions.push_back("(b)eg for another option");
	printActions(traderActions);

	std::string input;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	if (input == "h")
	{
		int playerHP = player->getHealth();
		player->recieveDamage(int(playerHP * 0.5));
		int playerDamage = player->getDamage();
		player->buffStrength(playerDamage);
		std::cout << "You feel weaker instantly, your health is now " << player->getHealth() << "." << std::endl;
		std::cout << "But your strength is incredible, your damage is now " << player->getDamage() << "." << std::endl;
		player->currentRoom->npcs.clear();
		puts("The room is empty...");
	}
	else if (input == "b")
	{
		player->currentRoom->npcs.clear();
		puts("A whisper of laughter fades and the room is empty...");
	}
	else
	{
		puts("Please only enter valid responses indicated by brackets, 'd' in (d)amage for example.\n");
	}
}

void Game::initiateRooms()
{
	room* room = player->currentRoom;

	std::vector<item>::const_iterator c_iter;
	
	if (!room->doors.empty() && room->enemies.empty())
	{
		puts("There is a locked door...");
		for(c_iter = player->inventory.begin(); c_iter != player->inventory.end(); ++c_iter)
		{
			if (c_iter->type == 3)
			{
				puts("Will you use the key to open the door?\n");
				puts("(y)es\n(n)o\n");
				std::string input;
				std::getline(std::cin, input);
				std::transform(input.begin(), input.end(), input.begin(), ::tolower);
				if (input == "y")
				{
					isGameOver = true;
				}
			}
		}
	}
	if (!player->currentRoom->enemies.empty())
	{
		engageCombat();
	}
	else if (!player->currentRoom->npcs.empty())
	{
		handleTrader();
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

void Game::printActions(std::vector<std::string> actions)
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		std::cout << actions[i] << ", ";
	}
	puts("what will you do?");
}

void Game::handleMovement()
{
	std::vector<std::string> actions = getMovementActions();
	puts("Looking around you there are doors leading: ");
	printActions(actions);
	
	std::string input;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	int horzMove = 0;
	int vertMove = 0;
	if (input == "w" && player->currentRoom->col > 0)
	{
		horzMove = -1;
	}	else if (input == "e" && player->currentRoom->col < dungeon->cols - 1)
	{
		horzMove = 1;
	}	else if (input == "n" && player->currentRoom->row > 0)
	{
		vertMove = -1;
	}	else if (input == "s" && player->currentRoom->row < dungeon->rows - 1)
	{
		vertMove = 1;
	}
	else
	{
		puts("Please only enter valid responses indicated by brackets, 'f' in (f)ight for example.\n");
	}

	room* newRoom = &dungeon->rooms[player->currentRoom->row + vertMove][player->currentRoom->col + horzMove];
	player->moveToRoom(newRoom);
}
