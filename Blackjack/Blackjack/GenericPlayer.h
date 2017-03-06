#pragma once
#include "Hand.h"

class GenericPlayer :
	public Hand
{
public:

	virtual bool IsHitting(sf::RenderWindow& window) = 0;
	bool CheckBust() const;
	
	GenericPlayer(const std::string& name);

private:
	enum class eMenuAction { HIT, QUIT, NOTHING };

	eMenuAction HandleClick(const sf::Vector2i& coordinates) const;

	
	struct MenuItem 
	{
		sf::Text m_text;
		sf::IntRect m_area;
		eMenuAction m_action;
	};

protected:
	bool AskForHit(sf::RenderWindow& window);
	std::string m_name;
	std::vector<MenuItem> m_buttons;
};