#include "TextureManager.h"

void TextureManager::LoadTexture(const std::string & textureName, const std::string & filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);

	m_textures.insert(std::make_pair(textureName, texture));
}

void TextureManager::LoadFont(const std::string & textureName, const std::string & filename)
{
	sf::Font font;
	font.loadFromFile(filename);

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