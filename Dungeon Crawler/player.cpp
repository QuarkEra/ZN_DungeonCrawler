#include "player.h"

Player::Player(std::string _name, int _health, int _damage): GameCharacter(_name, _health, _damage)
{	
}

std::vector<item> inventory;

void Player::heal(int amount)
{
	currentHealth += amount;
	if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}
}

void Player::moveToRoom(room* choice)
{
	previousRoom = currentRoom;
	currentRoom = choice;
}

void Player::retreat()
{
	room* tempRoom = currentRoom;
	currentRoom = previousRoom;
	previousRoom = tempRoom;
}

void Player::pickUpItem(struct item item)
{
	damage += item.damage;
	currentHealth += item.health;
	heal(item.health);
}

void Player::buffStrength(int _damage)
{
	damage += _damage;
}
