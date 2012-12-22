#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <vector>

class Graphics
{
public:
    static void loadTilemap(std::string const& fileName,
                            std::string const& name,
                            int tileSize);
    static sf::Texture const& getTexture(std::string const& tileset, int i);
    static bool tilesetIsLoaded(std::string const&);
private:
    static std::map<std::string,std::vector<sf::Texture*>> _graphics;
};
#endif
