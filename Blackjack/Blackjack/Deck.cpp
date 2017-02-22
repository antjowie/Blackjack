#include "Deck.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include <algorithm>

#if Debug
#include<iostream>
#endif // Debug


void Deck::Fill()
{
	if (DebugMode)
	{
		std::cout << "\n_DEBUG_ Filling cards in deck object _DEBUG_\n";
	}
	for (int rank = 1; rank <= 13; ++rank)
	{
		for (int suit = 0; suit <= 3; ++suit)
		{
			Add(new Card(TextureManager::GetTexture("Playing Cards"), rank, suit, true));
		}
	}
}

void Deck::Shuffle()
{
	if (DebugMode)
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

void Deck::DrawToWindow(sf::RenderWindow & window, const float & handNumber)
{
	m_hand.front()->Flip();
	m_hand.front()->Draw(window, handNumber * 90,0);
	m_hand.front()->Flip();
}

int Deck::GetTotalCards() const
{
	return m_hand.size();
}


Deck::Deck()
{
	m_hand.reserve(52);
}