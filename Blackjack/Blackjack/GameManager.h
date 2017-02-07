#pragma once
#include <vector>
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"

class GameManager
{
public:
	bool Play();
	void Instructions();
	void PrintPlayers();

	GameManager(const std::vector<std::string>& names);
	~GameManager();

private:
	Deck m_deck;
	std::vector<Player*> m_players;
	Dealer m_dealer;
};

