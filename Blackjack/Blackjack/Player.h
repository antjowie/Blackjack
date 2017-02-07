#pragma once
#include "GenericPlayer.h"

class Player :
	public GenericPlayer
{
public:
	virtual bool IsHitting() const;
	std::string& GetName();

	Player(const std::string& name);
};