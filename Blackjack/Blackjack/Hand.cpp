#include "Hand.h"
#include "GlobalVariables.h"

#if Debug
#include <iostream>
#endif // Debug


void Hand::Add(Card* const card)
{
	m_hand.push_back(card);
}

void Hand::Clear()
{
	if (DebugMode) std::cout << "\n_DEBUG_ Clearing hand object _DEBUG_\n";
	for (std::vector<Card*>::iterator iter = m_hand.begin(); iter != m_hand.end(); ++iter)
	{
		delete *iter;
		*iter = 0;
	}
	m_hand.clear();
}

int Hand::GetTotal() const
{
	int total = 0;
	bool containsAce = false;
	for (std::vector<Card*>::const_iterator iter = m_hand.begin(); iter != m_hand.end(); ++iter)
	{
		total += (*iter)->GetRank();
		if ((*iter)->GetRank() == 1)
		{
			containsAce = true;
		}
	}
	if (total <= 11 && containsAce)
	{
		total += 10;
	}
	return total;
}

void Hand::DrawToWindow(sf::RenderWindow & window, const float & handNumber)
{
	float offset = 0;
	for (std::vector<Card*>::const_iterator iter = m_hand.begin(); iter != m_hand.end(); ++iter, ++offset)
	{
		(*iter)->Draw(window, handNumber * 90, offset * 55);
	}
}

Hand::Hand()
{
	m_hand.reserve(4);
}

Hand::~Hand()
{
	if (DebugMode) std::cout << "\n_DEBUG_ Deleting hand object _DEBUG_\n";
	Clear();
}

std::ostream & operator<<(std::ostream & os, const Hand & hand)
{
	for (std::vector<Card*>::const_iterator iter = hand.m_hand.begin(); iter != hand.m_hand.end(); ++iter)
	{
		os << *(*iter) << '\t';
	}
	if (ShowTotal)
	{
		os << '(' <<hand.GetTotal() << ')';
	}
	return os;
}
