#include "Entity.hpp"

#include "Game.hpp"

Entity::Entity(int x, int y)
    : _visible(true), _solid(false),  _gameState(NULL), _state(0), _dialogue(NULL)
{ 
    _pos.x = x; 
    _pos.y = y; 
    _sprite.setPosition(_pos.x,_pos.y);
    _hitbox.left = _pos.x;
    _hitbox.top  = _pos.y;
}

Entity::Entity(sf::Vector2i const& pos)
    : _visible(true), _solid(false), _gameState(NULL), _state(0), _dialogue(NULL)
{
    _pos = pos;
    _sprite.setPosition(_pos.x,_pos.y);
    _hitbox.left = _pos.x;
    _hitbox.top  = _pos.y;
}

Entity::~Entity()
{
    if(_dialogue)
    {
        delete _dialogue;
    }
}

void Entity::setTexture(sf::Texture const& texture)
{ 
    _sprite.setTexture(texture);
    _hitbox.width = _sprite.getTextureRect().width;
    _hitbox.height = _sprite.getTextureRect().height;
}

void Entity::update() { }

void Entity::draw()
{
    if(_visible)
    {
        Game::window.draw(_sprite,sf::RenderStates::Default);
    }
}

void Entity::interact()
{
    displayDialogue();
}

void Entity::displayDialogue()
{
    if(_dialogue)
    {
        Game::displayDialogue(_dialogue,this);
    }
}

void Entity::setState(int i)
{
    _state = i;
}
