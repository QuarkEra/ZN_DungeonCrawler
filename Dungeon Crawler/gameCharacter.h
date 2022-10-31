#include <string>

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

class GameCharacter
{
protected:
	int maxHealth;
	int currentHealth;
	std::string name;
	int damage;

public:
	GameCharacter(std::string, int, int);

	void recieveDamage(int);
	bool isAlive();
	std::string getName();
	int getHealth();
	int getDamage();
};

#endif // !GAMECHARACTER_H