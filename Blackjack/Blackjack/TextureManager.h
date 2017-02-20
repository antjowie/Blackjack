#pragma once
#include <map>
#include "SFML\Graphics.hpp"

class TextureManager
{
public:

	static void LoadTexture(const std::string& textureName, const std::string& filename);
	static void LoadFont(const std::string& textureName, const std::string& filename);

	const static sf::Texture& GetTexture(const std::string& textureName);
	const static sf::Font& GetFont(const std::string& fontName);

private:
	static std::map<std::string, sf::Texture> m_textures;
	static std::map<std::string, sf::Font> m_fonts;
};
