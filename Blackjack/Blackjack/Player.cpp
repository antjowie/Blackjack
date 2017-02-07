#include "Player.h"
#include <iostream>
#include <string>

bool Player::IsHitting() const
{
	std::cout << "Does " << m_name << " want to hit? (Y/N) ";
	char input;
	std::cin >> input;
	return ((input == 'y') || (input == 'Y'));
}

std::string & Player::GetName()
{
	return m_name;
}

Player::Player(const std::string & name) :
	GenericPlayer(name)
{
}