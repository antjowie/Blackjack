#include "GameManager.h"
#include <iostream>
#include <string>
#include <time.h>


bool GameManager::Play()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Blackjack output window");
	window.setVerticalSyncEnabled(true);

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
		while ((!turns->CheckBust()) && (turns->IsHitting(window)))
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

bool GameManager::Play2()
{
	sf::RenderWindow window(sf::VideoMode(1024,768), "Blackjack output window");
	window.setVerticalSyncEnabled(true);

	sf::Event event;
	while (window.isOpen())
	{
	
	m_deck.Fill();
	m_deck.Shuffle();
	
	for (int i = 0; i < 2; ++i)
	{
		m_dealer.Add(m_deck.Draw());
	}
	m_dealer.FlipFirstCard();

	window.clear(sf::Color::Black);
	PrintHandsToWindow(window);
	window.display();

		while (window.pollEvent(event))
		{
			if ((event.type == event.Closed)) 
			window.close();
		}
		
		int playerNumber = 0;
		for (std::vector<Player*>::const_iterator player = m_players.begin(); player != m_players.end(); ++player, ++ playerNumber)
		{
			window.clear(sf::Color::Black);
			PrintHandsToWindow(window,playerNumber);
			(*player)->PrintButtons(window);
			window.display();
			while ((!(*player)->CheckBust()) && ((*player)->IsHitting(window)))
			{ 
				window.clear(sf::Color::Black);
				(*player)->Add(m_deck.Draw());
				(*player)->PrintButtons(window);
				PrintHandsToWindow(window,playerNumber);
				window.display();
			}
			window.clear(sf::Color::Black);
		}

		int highestPlayer = 0;
		for (auto getHighest : m_players)
		{
			if (getHighest->GetTotal() > highestPlayer && getHighest->GetTotal() <= 21)
			{
				highestPlayer = getHighest->GetTotal();
			}
		}

		m_dealer.FlipFirstCard();
		while (m_dealer.GetTotal() < highestPlayer) // m_dealer.IsHitting() is not needed
		{
			m_dealer.Add(m_deck.Draw());

			window.clear(sf::Color::Black);
			PrintHandsToWindow(window);
			window.display();
		}


		const int DEALER_TOTAL = m_dealer.GetTotal();
		std::cout << "...Calculating status...\n";
		std::cout << "Dealer had a total value of " << m_dealer.GetTotal() << ".\n";
		for (auto qualifier : m_players)
		{
			if ((m_dealer.CheckBust() || qualifier->GetTotal() > DEALER_TOTAL) && !qualifier->CheckBust())
			{
				std::cout << qualifier->GetName() << " has won. (" << qualifier->GetTotal() << ")\n";
			}
			else if (qualifier->GetTotal() < DEALER_TOTAL || qualifier->CheckBust())
			{
				std::cout << qualifier->GetName() << " has busted. (" << qualifier->GetTotal() << ")\n";
			}
			else
			{
				std::cout << qualifier->GetName() << " has pushed. (" << qualifier->GetTotal() << ")\n";
			}
			qualifier->Clear();
		}

		m_players[0]->IsHitting(window);

		m_dealer.Clear();
		m_deck.Clear();
	}
	return false;
}

void GameManager::PrintHandsToWindow(sf::RenderWindow & window, const int& playingHand)
{
	
	float handNumber = 0;
	sf::Text name("N/A", TextureManager::GetFont("Roboto"));
	for (std::vector<Player*>::const_iterator iter = m_players.begin(); iter != m_players.end(); ++iter, ++handNumber)
	{

		name.setPosition(sf::Vector2f(90.f * handNumber, 0));
		name.setScale(sf::Vector2f(1, 1));
		if(handNumber == playingHand)
		{
			name.setFillColor(sf::Color::Red);
		}
		else
		{
			name.setFillColor(sf::Color::White);
		}
		std::string firstName = (*iter)->GetName();
		if (firstName.find(" ") != std::string::npos)
		{
			firstName.erase(firstName.find(" "), firstName.size());
		}
		name.setString(firstName);
		name.scale(sf::Vector2f(82.f/name.getLocalBounds().width, 1));
	
		window.draw(name);

		(*iter)->DrawToWindow(window, handNumber);
	}
	name.setFillColor(sf::Color::Cyan);
	name.setScale(0.95f, 0.95f);
	
	name.setPosition(sf::Vector2f(90.f * 9.4f, 0));
	name.setString("Dealer");
	
	window.draw(name);
	m_dealer.DrawToWindow(window,9.4f);

	name.setPosition(sf::Vector2f(90.f* 10.5f, 0));
	name.setString("Deck");
	
	window.draw(name);
	m_deck.DrawToWindow(window, 10.4f);
}

GameManager::GameManager(const std::vector<std::string>& names)
{
	srand(static_cast<unsigned int>(time(NULL)));

	for (auto iter : names)
	{
		m_players.push_back(new Player(iter));
	}
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