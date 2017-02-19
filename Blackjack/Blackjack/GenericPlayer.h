#pragma once
#include "Hand.h"

class GenericPlayer :
	public Hand
{
public:

	virtual bool IsHitting() const = 0;
	bool CheckBust() const;
	
	void DrawToWindow(sf::RenderWindow& window, const float& handNumber);

	GenericPlayer(const std::string& name);

protected:
	std::string m_name;
};