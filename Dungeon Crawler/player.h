#include "room.cpp"
#include "gameCharacter.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public GameCharacter
{
private:
	room* previousRoom{};

public:
	Player(std::string, int, int);

	room* currentRoom{};

	void heal(int);
	void moveToRoom(room*);
	void retreat();
	void pickUpItem(item);
	void buffStrength(int);
};

#endif // !PLAYER_H

