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
