#include "Dealer.h"



int Dealer::IsHitting(sf::RenderWindow& window) 
{
	return (GetTotal() <= 16);
}

void Dealer::FlipFirstCard()
{
	m_hand[0]->Flip();
}

Dealer::Dealer() :
	GenericPlayer("Dealer")
{
}
