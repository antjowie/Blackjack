#include "Card.h"
#include <string>


int Card::GetRank() const
{
	if (m_isFaceUp)
	{
		return static_cast<int>(m_rank);
	}
	else
	{
		return 0;
	}
}

void Card::Flip()
{
	m_isFaceUp = !m_isFaceUp;
}

Card::Card(const int pRANK, const int pSUIT, const bool pIsFaceUp) :
	m_rank(static_cast<RANK>(pRANK)),
	m_suit(static_cast<SUIT>(pSUIT)),
	m_isFaceUp(pIsFaceUp)
{
}

std::ostream & operator<<(std::ostream & os, const Card & card)
{	
	if (card.m_isFaceUp)
	{
		// Convert rank to string
		const std::string RANKS[]
		{
			"0", "A", "2", "3", "4", "5", "6" , "7", "8", "9", "10",
			"J", "Q", "K"
		};
		// Convert suit to string
		const std::string SUITS[]
		{
			"h","s","c","d"
		};

		os << RANKS[card.m_rank] << SUITS[card.m_suit];
	}
	else
	{
		os << "XX";
	}

	return os;
}
