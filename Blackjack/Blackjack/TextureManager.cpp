#include "TextureManager.h"

#include <iostream>

void TextureManager::LoadTexture(const std::string & textureName, const std::string & filename)
{
	sf::Texture texture;
	if (!(texture.loadFromFile(filename)))
		std::cout << "A file couldn't be loaded, please check if a \'Texture\' folder is located in the root of your .exe file\n"
		<< "If not, download the file @ https://github.com/antjowie/Blackjack/tree/master/Blackjack/Blackjack or replace it\n\a";

	m_textures.insert(std::make_pair(textureName, texture));
}

void TextureManager::LoadFont(const std::string & textureName, const std::string & filename)
{
	sf::Font font;
	if (!(font.loadFromFile(filename)))
		std::cout << "A file couldn't be loaded, please check if a \'Texture\' folder is located in the root of your .exe file\n"
		<< "If not, download the file @ https://github.com/antjowie/Blackjack/tree/master/Blackjack/Blackjack or replace it\n\a";
	m_fonts.insert(std::make_pair(textureName, font));
}

const sf::Texture & TextureManager::GetTexture(const std::string & textureName)
{
	return m_textures.at(textureName);
}
const sf::Font & TextureManager::GetFont(const std::string & fontName)
{
	return m_fonts.at(fontName);
}
std::map<std::string, sf::Texture> TextureManager::m_textures;
std::map<std::string, sf::Font> TextureManager::m_fonts;