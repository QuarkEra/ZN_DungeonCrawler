#include "gameCharacter.h"


GameCharacter::GameCharacter() {
	name = {};
	damage = {};
	maxHealth = {};
	currentHealth = {};
}

GameCharacter::GameCharacter(std::string _name, int _health, int _damage)
{
	name = _name;
	damage = _damage;
	maxHealth = _health;
	currentHealth = _health;
}

void GameCharacter::recieveDamage(int amount)
{
	currentHealth -= amount;
}

bool GameCharacter::isAlive()
{
	return currentHealth > 0;
}

std::string GameCharacter::getName()
{
	return name;
}

int GameCharacter::getHealth()
{
	return currentHealth;
}

int GameCharacter::getDamage()
{
	return damage;
}