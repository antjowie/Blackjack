#include "Dealer.h"



bool Dealer::IsHitting() const
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
