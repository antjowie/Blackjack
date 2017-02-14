#include "GameManager.h"
#include <iostream>
#include <string>
#include <time.h>


bool GameManager::Play()
{
	m_deck.Fill();
	m_deck.Shuffle();
	
	for (int i = 0; i < 2; ++i)
	{
		m_dealer.Add(m_deck.Draw());
	}
	m_dealer.FlipFirstCard();
	
	std::cout << "\n...Players are playing...\n";
	for (auto turns : m_players)
	{
		PrintPlayers();
		turns->Add(m_deck.Draw());
		std::cout << '\n' << turns->GetName() << "\t|" << *turns << '\n';
		while ((!turns->CheckBust()) && (turns->IsHitting()))
		{
			turns->Add(m_deck.Draw());
			std::cout << '\n' << turns->GetName() << "\t|" << *turns << '\n';	
		}
	}

	std::cout << "...Dealer is playing...\n";
	m_dealer.FlipFirstCard();
	std::cout << "Dealer\t|" << m_dealer << '\n';
	
	int highestPlayer = 0;
	for (auto getHighest : m_players)
	{
		if (getHighest->GetTotal() > highestPlayer && getHighest->GetTotal() <= 21 )
		{
			highestPlayer = getHighest->GetTotal();
		}
	}

	while (m_dealer.GetTotal() < highestPlayer) // m_dealer.IsHitting() is not needed
	{
		m_dealer.Add(m_deck.Draw());
		std::cout << "Dealer\t|" << m_dealer << '\n';
	}

	const int DEALER_TOTAL= m_dealer.GetTotal();	
	std::cout << "...Calculating status...\n";
	for (auto qualifier : m_players)
	{
		if ((m_dealer.CheckBust() || qualifier->GetTotal() > DEALER_TOTAL) && !qualifier->CheckBust())
		{
			std::cout << qualifier->GetName() << " has won.\n";
		}
		else if (qualifier->GetTotal() < DEALER_TOTAL || qualifier->CheckBust())
		{
			std::cout << qualifier->GetName() << " has busted.\n";
		}
		else
		{
			std::cout << qualifier->GetName() << " has pushed.\n";
		}
		qualifier->Clear();
	}

	m_dealer.Clear();
	m_deck.Clear();

	char input;
	std::cout << "Want to play another game? (Y/N)\n";
	std::cin >> input;
	
	return ((input == 'Y') || (input == 'y'));
}

void GameManager::Instructions()
{
	std::cout << "Welcome to the blackjack game!\n"
		<< "The basic rules of blackjack is to get the highest combination of cards. \n"
		<< "Each card is worth its numeric value. (ace = 1/11, 2 = 2, jack = 11, queen = 12 etc. \n"
		<< "If your hands combination is higher than 21, you'll bail. The objective is to beat the bank. \n"
		<< "The ones with the highest hand will win. The bank will win from you if your combination is equal \n"
		<< "or lower than that of the bank. You'll get the option to hit. If you hit, you'll get a card. \n"
		<< "You can do this endlessly but remember, if you're over 21, you'll lose. At the end all hands will \n"
		<< "be compared. That's it! \n"
		<< "Press enter to continue..." << std::flush;
	std::cin.ignore();
}

void GameManager::PrintPlayers()
{
	std::cout << "\n...Listing all the players hand...\n"
		<< "Player\t|Cards\n";
		for (auto players : m_players)
		{
			std::cout << players->GetName() << "\t|" << *players << '\n';
		}
		std::cout << "Dealer\t|" << m_dealer << '\n';
}

void GameManager::Play2()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Blackjack");
	window.setVerticalSyncEnabled(true);
	sf::Event event;

	std::vector<std::string> namez;
	GameManager manager(namez);
	Deck deck;
	deck.Fill();
	Hand hand;
	hand.Add(deck.Draw());

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::Black);
		hand.DrawAll(window);
		window.display();
	}

}


GameManager::GameManager(const std::vector<std::string>& names)
{
	for (auto iter : names)
	{
		m_players.push_back(new Player(iter));
	}
	srand(static_cast<unsigned int>(time(NULL)));

	TextureManager::LoadTexture("Playing Cards", "Textures/playingCards2.png");
}


GameManager::~GameManager()
{
	for (auto destructor : m_players)
	{
		destructor->Clear();
	}
	m_deck.Clear();
	m_dealer.Clear();
}