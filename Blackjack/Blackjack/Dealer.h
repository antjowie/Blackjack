#pragma once
#include "GenericPlayer.h"

class Dealer :
	public GenericPlayer
{
public:
	virtual bool IsHitting(sf::RenderWindow& window);
	void FlipFirstCard();
	
	Dealer();
};

