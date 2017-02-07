#include "Deck.h"
#include "Card.h"
#include "GlobalVariables.h"
#include <algorithm>

#if Debug
#include<iostream>
#endif // Debug


void Deck::Fill()
{
	if (Debug)
	{
		std::cout << "\n_DEBUG_ Filling cards in deck object _DEBUG_\n";
	}
	for (int rank = Card::ACE; rank <= Card::KING; ++rank)
	{
		for (int suit = Card::HEARTS; suit <= Card::DIAMONDS; ++suit)
		{
			Add(new Card(rank, suit, true));
		}
	}
}

void Deck::Shuffle()
{
	if (Debug)
	{
		std::cout << "\n_DEBUG_ Shuffling cards in deck object _DEBUG_\n";
	}
	std::random_shuffle(m_hand.begin(), m_hand.end());
}

Card * Deck::Draw()
{
	if (m_hand.empty()) 
	{
		Fill();
		Shuffle();
	}
	Card* returner = m_hand.back();
	m_hand.pop_back();
	return returner;
}

int Deck::GetTotalCards() const
{
	return m_hand.size();
}


Deck::Deck()
{
	m_hand.reserve(52);
}