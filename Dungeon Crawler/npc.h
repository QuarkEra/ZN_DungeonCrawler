#include "gameCharacter.h"

#ifndef NPC_H
#define NPC_H

class NPC: public GameCharacter
{
public:
	NPC();
	NPC(std::string, int, int);

	void tradeHealthForDamage();
	void tradeDamageForHealth();
};

#endif
