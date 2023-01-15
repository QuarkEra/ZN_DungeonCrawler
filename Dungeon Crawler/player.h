#include "room.cpp"
#include "gameCharacter.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public GameCharacter
{
private:
	room* previousRoom{};

public:
	Player(const std::string&, int, int);

	room* currentRoom{};
	std::vector<item> inventory;

	void heal(int);
	void moveToRoom(room*);
	void retreat();
	void pickUpItem(struct item);
	void buffStrength(int);
};

#endif

