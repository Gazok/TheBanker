#pragma once
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Entity.hpp"
#include "GameState.hpp"

class Map
{
public:
    void loadMap(std::string const& fileName,GameState* state);
private:
    sf::Vector2i _dimensions;
    int _tileSize;
};
#endif
