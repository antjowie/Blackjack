#include "GameManager.h"
#include "GlobalVariables.h"

#include <cctype>
#include <fstream>
#include <string>

int main()
{
	TextureManager::LoadTexture("Background", "Textures/background.jpg");
	TextureManager::LoadTexture("Playing Cards", "Textures/playingCards2.png");
	TextureManager::LoadFont("Roboto", "Textures/Roboto.ttf");
	std::vector<std::string> names;

	std::cout << "Welcome to the Blackjack game.\n";

	std::ifstream readNameFile("names.txt", std::ios::beg);
	if (readNameFile.is_open())
	{
		char input;
		do
		{
			std::cout << "Data of the last game is saved, do you want to load it? (Y/N): ";
			std::cin >> input;
			input = toupper(input);
		} while (input != 'Y' && input != 'N');
		std::cin.ignore(1000, '\n');
		if (input == 'Y')
		{
			std::string name;
			while (std::getline(readNameFile, name))
			{
				names.push_back(name);
			} 
			std::cout << "The names: \n";
			for (auto iter : names)
			{
				std::cout << iter << '\n';
			}
			std::cout << "Have been loaded";
			readNameFile.close();

			std::cout << "\n---\nThe game window will now open, if the console doesn't close after the window is closed,\n"
				<< "please close the console manually to avoid memory leaks.\n---\n";

			GameManager game(names);
			game.Play2();

			std::cout << "\nThanks for playing!\n";

			return 0;
		}
		else
		{
			do
			{
				std::cout << "Do you want to delete the save file? (Y/N): ";
				std::cin >> input;
				input = toupper(input);
			} while (input != 'Y' && input != 'N');
			std::cin.ignore(1000, '\n');
			if (input == 'Y')
			{
				remove("names.txt");
			}
		}
	}

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

	std::ofstream writeNameFile("names.txt", std::ios::beg);
	std::string name;
	for (int i = 1; i < numberOfPlayers + 1; ++i)
	{
		std::cout << "Please enter the (full) name of player " << i << " : ";
		std::getline(std::cin, name);
		//std::cin >> name;
		names.push_back(name);
		if (writeNameFile.is_open())
		{
			writeNameFile << name << '\n';
		}
	}
	writeNameFile.close();
	
	std::cout << "\n---\nThe game window will now open, if the console doesn't close after the window is closed,\n"
		<< "please close the console manually to avoid memory leaks.\n---\n";

	GameManager game(names);
	game.Play2();
	
	std::cout << "\nThanks for playing!\n";
	return 0;
}