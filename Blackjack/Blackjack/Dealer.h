#pragma once
#include "GenericPlayer.h"

class Dealer :
	public GenericPlayer
{
public:
	virtual int IsHitting(sf::RenderWindow& window);
	void FlipFirstCard();
	
	Dealer();
};

