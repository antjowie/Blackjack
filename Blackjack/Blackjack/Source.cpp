#include "GameManager.h"
#include "GlobalVariables.h"
#include <string>

int main()
{
	TextureManager::LoadTexture("Playing Cards", "Textures/playingCards2.png");
	TextureManager::LoadFont("Roboto", "Textures/Roboto.ttf");

	std::vector<std::string> namez;

	for (int i = 0; i < 9; ++i)
	{
		std::string name = "Name";
		name += std::to_string(i);
		namez.push_back(name);
	}

	GameManager gamez(namez);
	gamez.Play2();


	return 0;

	std::cout << "Welcome to the BlackJack game.\n";

	int numberOfPlayers;
	do 
	{
		std::cout << "Please enter the number of players (1-9): ";
		std::cin >> numberOfPlayers;
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

	GameManager game(names);
	if (ShowInstructions)
	{
		game.Instructions();
	}
	
	while (game.Play());
	std::cout << "\nThanks for playing!\n";
	return 0;
}