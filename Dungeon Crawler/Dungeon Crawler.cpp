
// Dungeon Crawler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "game.h"

int main()
{
	std::string name;
	//puts("Greetings, brave adventurer! What is thy name?");
	//std::getline(std::cin, name);
	Player player = Player("name", 100, 10);
	
	//std::cout << "Luck be with you, " << player.getName() << "." << std::endl;

	Dungeon dungeon;
	NPC trader;
	Game game = Game(&player, &dungeon, &trader);

	while (!game.isGameOver)
	{
		game.initiateRooms();
		std::this_thread::sleep_for(std::chrono::milliseconds(66));
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
