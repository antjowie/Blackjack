#pragma once
#include "Hand.h"

class Deck : 
	public Hand
{
public:
	
	void Fill();
	void Shuffle();
	Card* Draw();
	
	void DrawToWindow(sf::RenderWindow& window, const float& handNumber);
	int GetTotalCards() const;

	Deck();
};

