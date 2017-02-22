#pragma once
#include "Hand.h"

class GenericPlayer :
	public Hand
{
public:

	virtual bool IsHitting(sf::RenderWindow& window) = 0;
	bool CheckBust() const;
	
	GenericPlayer(const std::string& name);

protected:
	bool AskForHit(sf::RenderWindow& window);
	std::string m_name;

private:
	bool HandleClick(const sf::Vector2f& coordinates) const;

	enum class eMenuAction { HIT, QUIT, NOTHING };

	
	struct MenuItem 
	{
		sf::Text m_text;
		sf::IntRect m_area;
		eMenuAction m_action;
	};

	std::vector<MenuItem> m_buttons;
};