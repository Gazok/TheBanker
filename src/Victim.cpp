#include "Victim.hpp"

#include "Game.hpp"
#include "Graphics.hpp"

//Remove
#include <iostream>

Victim::Victim(int x, int y) : Entity(x,y),_dialogue2(NULL)
{
    _victimized = false;
    _removed = false;
} 

Victim::~Victim()
{
    if(_dialogue2)
    {
        delete _dialogue2;
    }
}

void Victim::update()
{
    if(Game::part > _part && !_removed)
    {
        _gameState->remove(this);
        _removed = true;
    }
}

void Victim::setState(int i)
{
    if(!_victimized)
    {
        _state = i;

        if(_state != 0 && _state != 2)
        { 
            _victimized = true;
            _sprite.setTexture(Graphics::getTexture(_tilesetName,_typeID + 1));
            ++Game::disguise;
        }
    }
}

void Victim::displayDialogue()
{
    if(_victimized)
    {
        if(_dialogue)
        {
            Game::displayDialogue(_dialogue,this);
        }
    }
    else
    {
        if(_dialogue2)
        {
            Game::displayDialogue(_dialogue2,this);
        }
    }
}
