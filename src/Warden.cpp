#include "Warden.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Game.hpp"
#include "DialogueTree.hpp"

Warden::Warden(int x, int y):Entity(x,y)
{
    _guardPos = _pos;
    _okayPos = _pos + sf::Vector2i(32,32);

    std::string name = "res/txt/warden";
    for(int i = 0; i < 6; ++i)
    {
        std::stringstream s;
        s << name << i << ".xml";
        boost::property_tree::ptree tree;
        boost::property_tree::read_xml(s.str(),tree);
        DialogueTree* dTree = new DialogueTree(tree);
        _dTrees.push_back(dTree);
    }

}

Warden::~Warden()
{
    _dialogue = NULL;
    for(auto tree : _dTrees)
    {
        if(tree)
        {
            delete tree;
        }
    }
}

void Warden::update()
{
    if(Game::disguise <= Game::part)
    {
        if(_pos.x != _guardPos.x)
        {
            _pos = _guardPos;
        }
    }
    _sprite.setPosition(_pos.x,_pos.y);
    _hitbox.left = _pos.x;
    _hitbox.top = _pos.y;
} 

void Warden::setState(int i)
{ 
    if(Game::disguise > Game::part)
    {
        _pos = _okayPos;
    }
}

void Warden::displayDialogue()
{
    if(Game::part == 0)
    {
        if(Game::disguise > Game::part)
        {
            _dialogue = _dTrees[1];
        }
        else
        {
            _dialogue = _dTrees[0];
        }

    }
    else if(Game::part == 1)
    {
        if(Game::disguise > Game::part)
        {
            _dialogue = _dTrees[3];
        }
        else
        {
            _dialogue = _dTrees[2];
        }
    }
    else if(Game::part == 2)
    {
        if(Game::disguise > Game::part)
        {
            _dialogue = _dTrees[5];
        }
        else
        {
            _dialogue = _dTrees[4];
        }
    }
    else
    {
        _dialogue = NULL;
    }

    Entity::displayDialogue();
} 
