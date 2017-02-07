#pragma once
#include "Hand.h"

class Deck : 
	public Hand
{
public:
	
	void Fill();
	void Shuffle();
	Card* Draw();
	int GetTotalCards() const;

	Deck();
};

