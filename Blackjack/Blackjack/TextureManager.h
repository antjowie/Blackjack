#pragma once
#include <map>
#include "SFML\Graphics.hpp"

class TextureManager
{
public:

	static void LoadTexture(const std::string& textureName, const std::string& filename);
	const static sf::Texture& GetTexture(const std::string& textureName);
	
private:
	static std::map<std::string, sf::Texture> m_textures;
};
