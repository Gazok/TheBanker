#include "MainState.hpp"

#include "Game.hpp"
#include "Map.hpp"

MainState::MainState()
{ 
    Map map;
    map.loadMap(std::string("testmap.json"),this);
    Game::disguise = 0;
    Game::part = -1;
}
