#pragma once
#include "GenericPlayer.h"

class Player :
	public GenericPlayer
{
public:
	virtual bool IsHitting() const;
	std::string& GetName();
	std::vector<Card*>& GetCards();

	Player(const std::string& name);
};