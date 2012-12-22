#include "GameState.hpp"

GameState::GameState()
{
}

GameState::~GameState()
{
    for (auto entity : entities)
    { 
        //TODO: Check that it hasn't moved world?
        delete entity;
    }
}

void GameState::add(Entity* entity)
{
    if(entity->_gameState == NULL)
    {
        entities.push_back(entity);
        entity->_gameState = this;
    }
}

//List entity to be removed when convenient
//and render it invisible until then
void GameState::remove(Entity* entity)
{
    if(entity->_gameState == this)
    {
        toRemove.push_back(entity);
        entity->_visible = false;
        entity->_solid = false;
    }
}

//Remove entities deleted in update phase
void GameState::deleteRemoved()
{ 
    bool removed;

    while(!toRemove.empty())
    {
        removed = false;

        for(std::vector<Entity*>::iterator it = entities.begin();
                it != entities.end();
                it++)
        { 
            if ( *it == toRemove.back())
            {
                entities.erase(it);
                removed = true;
                break;
            }
        }

        if(removed)
        {
            delete toRemove.back();
        }
        toRemove.pop_back();
    }
}

//Update all stored entities
void GameState::update() 
{
    for(auto entity : entities)
    {
        entity->update();
    }
    deleteRemoved();
}

//Draw all stored entities
void GameState::draw()
{
    for(auto entity : entities)
    {
        entity->draw();
    }
}

std::vector<Entity*> GameState::collide(Entity* entA,sf::Vector2i const& offset)
{ 
    std::vector<Entity*> list;

    sf::IntRect hitbox1 = entA->getHitbox();
    hitbox1.left += offset.x;
    hitbox1.top  += offset.y;

    sf::IntRect hitbox2;

    for(auto entB : entities)
    {
        if(entB == entA) continue;

        hitbox2 = entB->getHitbox();

        if(hitbox1.intersects(hitbox2))
        {
            list.push_back(entB);
        }
    }

    return list; 
}
