#pragma once
#include <iostream>

class Card
{
	friend std::ostream& operator<<(std::ostream& os, const Card& card);
public:

	enum RANK 
	{
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};
	enum SUIT
	{
		HEARTS, SPADES, CLUBS, DIAMONDS
	};

	int GetRank() const;
	void Flip();

	Card(const int RANK = 0, const int SUIT = 0, const bool isFaceUp = true);

private:

	RANK m_rank;
	SUIT m_suit;

	bool m_isFaceUp;
};

