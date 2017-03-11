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
	bool Play2();


	GameManager(const std::vector<std::string>& names);
	~GameManager();

private:

	enum class eMainMenuAction{ play, instructions, exit, nothing};
	enum class eEndMenuAction{ replay, quit, nothing};
	
	struct MenuItem 
	{
		eMainMenuAction m_action;
		sf::IntRect m_area;
		sf::Text m_text;
	};
	
	eMainMenuAction MainMenu(sf::RenderWindow& window);
	eMainMenuAction HandleMainMenuInput(const sf::Vector2i& eventCoordinates, const std::vector<MenuItem>& menuActions);
	eEndMenuAction EndMenu(sf::RenderWindow& window);

	void Instructions(sf::RenderWindow& window);
	void PrintPlayers();
	void PrintHandsToWindow(sf::RenderWindow& window, const int& playingHand = 10);
	void PrintTextEvent(sf::RenderWindow& window, const std::string event = "N/A");

	std::deque<std::string> m_textEvents;
	Deck m_deck;
	std::vector<Player*> m_players;
	Dealer m_dealer;
};

