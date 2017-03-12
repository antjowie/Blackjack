#include "GenericPlayer.h"
#include "TextureManager.h"
#include "SFML\Graphics.hpp"

GenericPlayer::GenericPlayer(const std::string& name) :
	m_name(name)
{
	m_hand.reserve(7);
	m_buttons.reserve(2);
	
	MenuItem hit,quit;
	hit.m_action = eMenuAction::HIT;
	hit.m_area = sf::IntRect(900-60,530-20, 195, 80);
	hit.m_text.setFont(TextureManager::GetFont("Roboto"));
	hit.m_text.setPosition(sf::Vector2f(910, 530));
	hit.m_text.setString("Hit");

	quit.m_action = eMenuAction::QUIT;
	quit.m_area = sf::IntRect(900-60, 650-20, 195, 80);
	quit.m_text.setFont(TextureManager::GetFont("Roboto"));
	quit.m_text.setPosition(sf::Vector2f(906, 650));
	quit.m_text.setString("Quit"); 

	m_buttons.push_back(hit);
	m_buttons.push_back(quit);
}

int GenericPlayer::AskForHit(sf::RenderWindow & window)
{
	sf::Event event;

	while (true)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					return 0;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					return 2;
				break;
			case sf::Event::Closed:
				return false;
				break;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				eMenuAction result = HandleClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				switch (result)
				{
				case GenericPlayer::eMenuAction::HIT:
					return 0;
					break;
				case GenericPlayer::eMenuAction::QUIT:
					return 2;
					break;
				case GenericPlayer::eMenuAction::NOTHING:
					break;
				}
			}
		}
	}
}

GenericPlayer::eMenuAction GenericPlayer::HandleClick(const sf::Vector2i& coordinates) const
{
	for (auto button : m_buttons)
	{
		if (button.m_area.contains(coordinates))
			return button.m_action;
	}
	return eMenuAction::NOTHING;
}

bool GenericPlayer::CheckBust() const
{
	return (GetTotal() > 21);
}

