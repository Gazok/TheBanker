#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Entity.hpp"

class GameState
{
public:
    GameState();
    virtual ~GameState();

    virtual void update();
    virtual void draw();

    std::vector<Entity*> collide(Entity*, sf::Vector2i const&);
    void add(Entity*);
    void remove(Entity*);
protected:
    void deleteRemoved();

    std::vector<Entity*> entities;
    std::vector<Entity*> toRemove;
};
#endif
