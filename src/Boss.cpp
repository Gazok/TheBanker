#include "Boss.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Game.hpp"
#include "DialogueTree.hpp"

Boss::Boss(int x, int y) : Entity(x,y)
{
    _state = 0;

    std::string name = "res/txt/boss";
    for(int i = 0; i < 4; ++i)
    {
        std::stringstream s;
        s << name << i << ".xml";
        boost::property_tree::ptree tree;
        boost::property_tree::read_xml(s.str(),tree);
        DialogueTree* dTree = new DialogueTree(tree);
        _dTrees.push_back(dTree);
    }
}

Boss::~Boss()
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

void Boss::displayDialogue()
{
    if(Game::defacedTables - 1 == Game::part)
    {
        _dialogue = _dTrees[Game::defacedTables];
        ++Game::part;
    }
    else
    {
        _dialogue = NULL;
    }

    Entity::displayDialogue();
} 

void Boss::setState(int i)
{
    if(Game::part == 3)
    {
        Game::end();
    }
}
