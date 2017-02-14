#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

class Card
{
	friend std::ostream& operator<<(std::ostream& os, const Card& card);
public:
	int GetRank() const;
	void Flip();

	void Draw(sf::RenderWindow& window);

	Card(const sf::Texture& texture, const int RANK = 0, const int SUIT = 0, const bool isFaceUp = true);

private:
	enum RANK 
	{
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};
	enum SUIT
	{
		HEARTS, DIAMONDS, CLUBS, SPADES
	};

	RANK m_rank;
	SUIT m_suit;
	sf::Sprite m_cardTexture;

	bool m_isFaceUp;
};

