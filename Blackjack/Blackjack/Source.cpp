#include "GameManager.h"
#include "GlobalVariables.h"
#include <string>

int main()
{
	TextureManager::LoadTexture("Background", "Textures/background.jpg");
	TextureManager::LoadTexture("Playing Cards", "Textures/playingCards2.png");
	TextureManager::LoadFont("Roboto", "Textures/Roboto.ttf");

	std::cout << "Welcome to the Blackjack game.\n";

	int numberOfPlayers;
	do 
	{
		std::cout << "Please enter the number of players (1-9): ";
		std::cin >> numberOfPlayers;
		
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100000,'\n');
			continue;
		}

	} while (numberOfPlayers < 1 || numberOfPlayers > 9);
	std::cin.ignore();

	std::vector<std::string> names;
	std::string name;
	for (int i = 1; i < numberOfPlayers + 1; ++i)
	{
		std::cout << "Please enter the (full) name of player " << i << " : ";
		std::getline(std::cin, name);
		//std::cin >> name;
		names.push_back(name);
	}

	std::cout << "The game window will now open, if the console doesn't close after the window is closed,\n"
		<< "please close the console manually to avoid memory leaks.\n";

	GameManager game(names);
	game.Play2();
	
	std::cout << "\nThanks for playing!\n";
	return 0;
}