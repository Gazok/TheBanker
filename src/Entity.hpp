#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Vector2.hpp> 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "DialogueTree.hpp"

class GameState;

class Entity
{
public:
    Entity(int x, int y);
    Entity(sf::Vector2i const&);
    virtual ~Entity();

    virtual void update();
    virtual void draw(); 

    virtual void interact();

    virtual void displayDialogue();

    bool isSolid() const { return _solid; }
    sf::IntRect const& getHitbox() const { return _hitbox; }
    sf::Vector2i const& getPosition() const { return _pos; }
    std::string const& getName() const { return _name; }
    int getState() const { return _state; }

    virtual void setState(int i);
    void setTexture(sf::Texture const&);
protected:
    sf::Vector2i _pos;
    sf::Sprite _sprite; 
    bool _visible;
    bool _solid;
    int _typeID;
    std::string _name;
    std::string _type;
    DialogueTree* _dialogue;
    sf::IntRect _hitbox; 
    int _state;

    std::string _tilesetName;

    GameState* _gameState;
    friend class GameState;
    friend class Map;
};
#endif
