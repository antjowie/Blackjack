#pragma once
#include <vector>
#include <deque>
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "TextureManager.h"

class GameManager
{
public:
	bool Play();
	void Instructions();
	void PrintPlayers();

	bool Play2();


	GameManager(const std::vector<std::string>& names);
	~GameManager();

private:

	enum eMainMenuAction{ play, instructions, exit};

	eMainMenuAction MainMenu(sf::RenderWindow& window);
	void PrintHandsToWindow(sf::RenderWindow& window, const int& playingHand = 10);
	void PrintTextEvent(sf::RenderWindow& window, const std::string event = "N/A");

	std::deque<std::string> m_textEvents;
	Deck m_deck;
	std::vector<Player*> m_players;
	Dealer m_dealer;
};

