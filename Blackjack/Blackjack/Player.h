#pragma once
#include "GenericPlayer.h"

class Player :
	public GenericPlayer
{
public:
	virtual int IsHitting(sf::RenderWindow& window);
	void PrintButtons(sf::RenderWindow& window);

	std::string& GetName();
	std::vector<Card*>& GetCards();

	Player(const std::string& name);
};