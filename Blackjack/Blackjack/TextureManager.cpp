#include "TextureManager.h"

void TextureManager::LoadTexture(const std::string & textureName, const std::string & filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);

	m_textures.insert(std::make_pair(textureName, texture));
}

const sf::Texture & TextureManager::GetTexture(const std::string & textureName)
{
	return m_textures.at(textureName);
}
std::map<std::string, sf::Texture> TextureManager::m_textures;

