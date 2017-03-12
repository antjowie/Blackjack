 #include "Player.h"
#include <iostream>
#include <string>

int Player::IsHitting(sf::RenderWindow& window)
{
	/*
	std::cout << "Does " << m_name << " want to hit? (Y/N) ";
	char input;
	std::cin >> input;
	return ((input == 'y') || (input == 'Y'));
	*/
	return AskForHit(window);
}

void Player::PrintButtons(sf::RenderWindow & window)
{
	sf::RectangleShape rect(sf::Vector2f(195, 80));
	rect.setFillColor(sf::Color::Color(255, 255, 255, 100));
	for (auto button : m_buttons)
	{
		window.draw(button.m_text);
		rect.setPosition(static_cast<float>(button.m_area.left), static_cast<float>(button.m_area.top));
		window.draw(rect);
	}

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

