#include <string>

#ifndef ITEM_CPP
#define ITEM_CPP

struct item
{
	std::string name;
	int type{}; // 1 = healing, 2 = damage
	int damage{};
	int health{};
	bool isConsumable;
	int uses;
	int maxUses;
};

#endif
