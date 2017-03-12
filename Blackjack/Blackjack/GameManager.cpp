#include "GameManager.h"
#include "Background.h"
#include "GlobalVariables.h"

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

void GameManager::Instructions(sf::RenderWindow& window)
{
	sf::Text instructions("Welcome to the blackjack game!\n"
		"The basic rules of blackjack is to \n"
		"get the highest combination of cards. \n"
		"Each card is worth its numeric value. \n"
		"(ace = 1/11, 2 = 2, jack = 11, queen = 12 etc.) \n"
		"If your hands combination is higher than 21, \n"
		"you'll bail. The objective is to beat the bank. \n"
		"The ones with the highest hand will win. \n"
		"The bank will win from you if your combination is equal \n"
		"or lower than that of the bank. You'll get \n"
		"the option to hit. If you hit, you'll get a card. \n"
		"You can do this endlessly but remember, if \n"
		"you're over 21, you'll lose. At the end all hands will \n"
		"be compared. That's it! You can draw a card with \n"
		"enter and stop with shift or use the buttons\n"
		" Press enter to return...", TextureManager::GetFont("Roboto"));
	instructions.setCharacterSize(40);
	
	window.clear(sf::Color::Black);
	Background::Draw(window);
	window.draw(instructions);
	window.display();

	sf::Event event;
	bool escape = true;
	while (escape)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Return)
					escape = false;
		}
	}
	/*
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
	*/
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
	sf::RenderWindow window(sf::VideoMode(1024,768), "Blackjack", sf::Style::Close | sf::Style::None);
	window.setVerticalSyncEnabled(true);

	sf::Event event;
	bool FirstLoop = true;
	while (window.isOpen())
	{
		if (FirstLoop)
		{
			eMainMenuAction result;
			while(true)
			{
				result = (MainMenu(window));
				
				if (result == GameManager::eMainMenuAction::play)
				{
					break;
				}
				if (result == GameManager::eMainMenuAction::instructions)
				{
					Instructions(window);
				}
				if (result == GameManager::eMainMenuAction::exit)
				{
					window.close();
					break;
				}
			}

			FirstLoop = false;
		}

		if (!window.isOpen())
		{
			return;
		}

		m_deck.Fill();
		m_deck.Shuffle();

		for (int i = 0; i < 2; ++i)
		{
			m_dealer.Add(m_deck.Draw());
		}
		m_dealer.FlipFirstCard();

		window.clear(sf::Color::Black);
		Background::Draw(window);
		PrintHandsToWindow(window);
		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
		}

		int playerNumber = 0;
		for (std::vector<Player*>::const_iterator player = m_players.begin(); player != m_players.end(); ++player, ++playerNumber)
		{
			window.clear(sf::Color::Black);
			Background::Draw(window);
			(*player)->PrintButtons(window);
			PrintHandsToWindow(window, playerNumber);

			const std::string eventText = "It is " + (*player)->GetName() + "\'s turn!";
			PrintTextEvent(window, eventText);

			window.display();

			bool playerInput;
			switch ((*player)->IsHitting(window))
			{
			case 0:
				playerInput = true;
				break;
			case 1:
				window.close();
				return;
				break;
			case 2:
				playerInput = false;
			}

			while ((!(*player)->CheckBust()) && (playerInput))
			{
				(*player)->Add(m_deck.Draw());

				window.clear(sf::Color::Black);
				Background::Draw(window);

				const std::string hitEvent = (*player)->GetName() + " hits";
				PrintTextEvent(window, hitEvent);

				(*player)->PrintButtons(window);
				PrintHandsToWindow(window, playerNumber);
				window.display();
				
				if (!(*player)->CheckBust())
				{
					switch ((*player)->IsHitting(window))
					{
					case 0:
						playerInput = true;
						break;
					case 1:
						window.close();
						return;
						break;
					case 2:
						playerInput = false;
					}
				}
			}
		
			window.clear(sf::Color::Black);
			Background::Draw(window);

			std::string statusEvent = (*player)->GetName();
			if ((*player)->GetTotal() == 21)
			{
				statusEvent += " has a blackjack!";
			}
			else if ((*player)->GetTotal() > 21)
			{
				statusEvent += " bails";
			}
			else
			{
				statusEvent += " quits";
			}

			PrintTextEvent(window, statusEvent);

			PrintHandsToWindow(window);
			window.display();
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
		while (m_dealer.GetTotal() < 16 && m_dealer.GetTotal() <= highestPlayer) // m_dealer.IsHitting() is not needed
		{
			m_dealer.Add(m_deck.Draw());

			window.clear(sf::Color::Black);
			Background::Draw(window);
			PrintHandsToWindow(window);
			window.display();
		}

		switch (EndMenu(window))
		{
		case eEndMenuAction::quit:
			window.close();
			break;
		case eEndMenuAction::replay:
			break;
		}

		m_dealer.Clear();
		m_deck.Clear();
	}
	return;
}

GameManager::eMainMenuAction GameManager::MainMenu(sf::RenderWindow& window)
{
	1024, 768;
	MenuItem play, instructions, quit;

	play.m_action = eMainMenuAction::play;
	play.m_area = sf::IntRect(500 - 60, 768 / 4 * 1 - 20, 195, 80);
	play.m_text.setFont(TextureManager::GetFont("Roboto"));
	play.m_text.setPosition(sf::Vector2f(505,768/4*1));
	play.m_text.setString("Play");

	instructions.m_action = eMainMenuAction::instructions;
	instructions.m_area = sf::IntRect(500- 60, 768 / 4 * 2 - 20, 195, 80);
	instructions.m_text.setFont(TextureManager::GetFont("Roboto"));
	instructions.m_text.setPosition(sf::Vector2f(460,768/4*2));
	instructions.m_text.setString("Instructions");

	quit.m_action = eMainMenuAction::exit;
	quit.m_area = sf::IntRect(500 - 60, 768 / 4 * 3 - 20, 195, 80);
	quit.m_text.setFont(TextureManager::GetFont("Roboto"));
	quit.m_text.setPosition(sf::Vector2f(505,768/4*3));
	quit.m_text.setString("Quit");

	std::vector<MenuItem> buttons;
	buttons.reserve(4);
	buttons.push_back(play);
	buttons.push_back(instructions);
	buttons.push_back(quit);

	sf::RectangleShape rect(sf::Vector2f(195, 80));
	rect.setFillColor(sf::Color::Color(255, 255, 255, 100));

	window.clear(sf::Color::Black);
	Background::Draw(window);

	for (auto button : buttons)
	{
		window.draw(button.m_text);
		rect.setPosition(static_cast<float>(button.m_area.left), static_cast<float>(button.m_area.top));
		window.draw(rect);
	}

	window.display();

	sf::Event event;

	while (true) 
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::MouseButtonPressed:
					return HandleMainMenuInput(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), buttons);
					break;
				case sf::Event::Closed:
					return eMainMenuAction::exit;
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::BackSpace)
						return eMainMenuAction::exit;
					else if (event.key.code == sf::Keyboard::Return)
						return eMainMenuAction::play;
					break;
			}
		}
	}
	return eMainMenuAction();
}

GameManager::eMainMenuAction GameManager::HandleMainMenuInput(const sf::Vector2i& eventCoordinates, const std::vector<MenuItem>& menuActions)
{
	for (auto iter : menuActions)
	{
		if (iter.m_area.contains(eventCoordinates))
		{
			if (DebugMode)
			{
				switch (iter.m_action)
				{
					case GameManager::eMainMenuAction::play:
						std::cout << "DEBUG BUTTON: Play\n";
						break;
					case GameManager::eMainMenuAction::instructions:
						std::cout << "DEBUG BUTTON: Instructions\n";
						break;
					case GameManager::eMainMenuAction::exit:
						std::cout << "DEBUG BUTTON: Exit\n";
						break;
					case GameManager::eMainMenuAction::nothing:
						std::cout << "DEBUG BUTTON: Nothing\n";
						break;
					default:
						std::cout << "DEBUG BUTTON: Default\n";
						break;
				}
			}
			return iter.m_action;
		}
	}
	return eMainMenuAction::nothing;
}

GameManager::eEndMenuAction GameManager::EndMenu(sf::RenderWindow & window)
{
	const int BANK_TOTAL = m_dealer.GetTotal();

	sf::RectangleShape blur(sf::Vector2f(1024, 768));
	blur.setFillColor(sf::Color(0,0,0, 225));
	window.draw(blur);

	sf::Text playerStatus("N/T", TextureManager::GetFont("Roboto"));
	std::string bank = "The bank has a total score off ";
	bank += std::to_string(BANK_TOTAL);
	playerStatus.setString(bank);
	window.draw(playerStatus);
	int offset = 1;
	for (auto qualifier : m_players)
	{
		std::string status = qualifier->GetName();
		if (!qualifier->CheckBust() && (m_dealer.CheckBust() || qualifier->GetTotal() > BANK_TOTAL))
		{
			status += " has won";
			playerStatus.setFillColor(sf::Color::Green);
		}
		else if (qualifier->CheckBust())
		{
			status += " has busted";
			playerStatus.setFillColor(sf::Color::Red);
		}
		else if (qualifier->GetTotal() == BANK_TOTAL)
		{
			status += " has pushed";
			playerStatus.setFillColor(sf::Color::White);
		}
		else 
		{
			status += " has lost";
			playerStatus.setFillColor(sf::Color::White);
		}
		status += " with a total score off " + std::to_string(qualifier->GetTotal());
		qualifier->Clear();

		playerStatus.setString(status);
		playerStatus.setPosition(sf::Vector2f(0, 30.f * offset));
		++offset;

		window.draw(playerStatus);
	}
	playerStatus.setPosition(sf::Vector2f(0, 30.f * ++offset + 10.f));
	playerStatus.setFillColor(sf::Color::White);
	playerStatus.setString("Press enter to play again or escape to quit");
	
	window.draw(playerStatus);
	window.display();

	sf::Event event;

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == event.KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					return eEndMenuAction::quit;
				else if (event.key.code == sf::Keyboard::Return)
					return eEndMenuAction::replay;
		}
	}
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

void GameManager::PrintTextEvent(sf::RenderWindow & window, const std::string event)
{
	if(event != "N/A")
	{ 
		while (m_textEvents.size() > 5)
		{
			m_textEvents.pop_back();
		}

		m_textEvents.push_front(event);
	}

	sf::RectangleShape rectangle(sf::Vector2f(835, 608));
	rectangle.setPosition(0, 500);
	rectangle.setFillColor(sf::Color(0, 0, 0, 100));
	window.draw(rectangle);
	
	sf::Text eventText(" ",TextureManager::GetFont("Roboto"));

	int textNumber = 0;
	for (auto text : m_textEvents)
	{
		eventText.setPosition(sf::Vector2f(0, 510));
		eventText.setString(text);
		eventText.move(sf::Vector2f(0, 30.f * textNumber));
		eventText.setFillColor(sf::Color(255, 255, 255, 255 - textNumber * 30));
		window.draw(eventText);

		++textNumber;
	}
}