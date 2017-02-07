#pragma once
#include "GenericPlayer.h"

class Dealer :
	public GenericPlayer
{
public:
	virtual bool IsHitting() const;
	void FlipFirstCard();
	
	Dealer();
};

