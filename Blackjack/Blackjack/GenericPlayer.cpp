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
	hit.m_area = sf::IntRect(910-60,530-20, 180, 80);
	hit.m_text.setFont(TextureManager::GetFont("Roboto"));
	hit.m_text.setPosition(sf::Vector2f(920, 530));
	hit.m_text.setString("Hit");

	quit.m_action = eMenuAction::QUIT;
	quit.m_area = sf::IntRect(910-60, 650-20, 180, 80);
	quit.m_text.setFont(TextureManager::GetFont("Roboto"));
	quit.m_text.setPosition(sf::Vector2f(912, 650));
	quit.m_text.setString("Quit"); 

	m_buttons.push_back(hit);
	m_buttons.push_back(quit);
}

bool GenericPlayer::AskForHit(sf::RenderWindow & window)
{
	sf::RectangleShape rect(sf::Vector2f(180,80));
	rect.setFillColor(sf::Color::Color(255,255,255,100));
	for (auto button : m_buttons)
	{
		window.draw(button.m_text);
		rect.setPosition(button.m_area.left, button.m_area.top);
		window.draw(rect);
	}
	return false;
}

bool GenericPlayer::HandleClick(const sf::Vector2f& coordinates) const
{
	return false;
}

bool GenericPlayer::CheckBust() const
{
	return (GetTotal() > 21);
}

