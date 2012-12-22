#include "Table.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Game.hpp"
#include "Graphics.hpp"
#include "DialogueTree.hpp"

Table::Table(int x, int y) : Entity(x,y)
{
    _defaced = false;

    std::string name = "res/txt/table";
    for(int i = 0; i < 3; ++i)
    {
        std::stringstream s;
        s << name << i << ".xml";
        boost::property_tree::ptree tree;
        boost::property_tree::read_xml(s.str(),tree);
        DialogueTree* dTree = new DialogueTree(tree);
        _dTrees.push_back(dTree);
    }
}

Table::~Table()
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

void Table::displayDialogue()
{
    if(!_defaced)
    {
        if(Game::part == 0 && Game::defacedTables == 0)
        {
            _dialogue = _dTrees[0];
        }
        else if(Game::part == 1 && Game::defacedTables == 1)
        {
            _dialogue = _dTrees[1];
        }
        else if(Game::part == 2 && Game::defacedTables == 2)
        {
            _dialogue = _dTrees[2];
        }
    }
    else
    {
        _dialogue = NULL;
    }

    Entity::displayDialogue();
} 

void Table::setState(int i)
{
    if(Game::defacedTables <= Game::part && !_defaced)
    { 
        ++Game::defacedTables;
        _sprite.setTexture(Graphics::getTexture(_tilesetName,_typeID + Game::defacedTables));
        _defaced = true;
    }
}
