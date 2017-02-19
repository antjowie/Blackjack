#include "GenericPlayer.h"



GenericPlayer::GenericPlayer(const std::string& name) :
	m_name(name)
{
	m_hand.reserve(7);
}

bool GenericPlayer::CheckBust() const
{
	return (GetTotal() > 21);
}

void GenericPlayer::DrawToWindow(sf::RenderWindow& window, const float& handNumber)
{
	float offset = 0;
	for (std::vector<Card*>::const_iterator iter = m_hand.begin();
		iter != m_hand.end(); ++iter, ++offset)
	{
		(*iter)->Draw(window, handNumber * 82, offset * 30);
	}
}