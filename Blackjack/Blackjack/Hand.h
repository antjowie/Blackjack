#pragma once
#include <vector>
#include "Card.h"

class Hand
{
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);
public:

	void Add(Card* const card);
	void Clear();
	int GetTotal() const;

	Hand();
	~Hand();

protected:
	std::vector<Card*> m_hand;
};

