 #include "Player.h"
#include <iostream>
#include <string>

bool Player::IsHitting(sf::RenderWindow& window)
{
	/*
	std::cout << "Does " << m_name << " want to hit? (Y/N) ";
	char input;
	std::cin >> input;
	return ((input == 'y') || (input == 'Y'));
	*/
	return AskForHit(window);
}

std::string & Player::GetName()
{
	return m_name;
}

std::vector<Card*>& Player::GetCards()
{
	return m_hand;
}

Player::Player(const std::string & name) :
	GenericPlayer(name)
{
}

