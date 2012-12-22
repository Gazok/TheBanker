#include "Map.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Game.hpp"
#include "Graphics.hpp"
#include "Player.hpp"
#include "Victim.hpp"
#include "Warden.hpp"
#include "Table.hpp"
#include "Boss.hpp"

void Map::loadMap(std::string const& fileName, GameState* state)
{
    std::stringstream filePath;

    filePath << "res/maps/";
    filePath << fileName;

    boost::property_tree::ptree mapTree;

    boost::property_tree::read_json(filePath.str(),mapTree);

    _dimensions.x = mapTree.get<int>("height");
    _dimensions.y = mapTree.get<int>("width");
    _tileSize = mapTree.get<int>("tileheight");

    //Load tiles into memory
    std::vector<std::vector<std::vector<int>>> tileMatrixArray;
    for (auto layer : mapTree.get_child("layers"))
    {
        std::vector<std::vector<int>> tileMatrix(_dimensions.y);
        for(int i = 0; i < _dimensions.y; ++i)
        {
            tileMatrix[i] = std::vector<int>(_dimensions.x);
        }

        sf::Vector2i pos(0,0);
        int entType;
        for(auto ent : layer.second.get_child("data"))
        {
            std::stringstream s;
            s << ent.second.data();
            s >> entType;
            tileMatrix[pos.y][pos.x] = entType;

            ++pos.x;
            if(pos.x >= _dimensions.x)
            {
                pos.x = 0;
                ++pos.y;
            } 
        } 
        tileMatrixArray.push_back(tileMatrix);
    }

    //Load tileset graphics
    for(auto tileset : mapTree.get_child("tilesets"))
    {
        std::string name = tileset.second.get<std::string>("name"); 

        if(!Graphics::tilesetIsLoaded(name))
        {
            std::stringstream anotherFilePath;
            anotherFilePath << "res/maps/" << tileset.second.get<std::string>("image");
            Graphics::loadTilemap(anotherFilePath.str(),name,_tileSize);
        }
    }

    //Load entities from tiles in memory
    for( auto tileMatrix : tileMatrixArray)
    {
        for(int i = 0; i < _dimensions.y; ++i)
        {
            for(int j = 0; j < _dimensions.x; ++j) 
            { 
                if(tileMatrix[i][j])
                {
                    Entity* ent;
                    const int id = tileMatrix[i][j] - 1;

                    //Load entity properties
                    for(auto tileset : mapTree.get_child("tilesets"))
                    {
                        const int tilesetGID = tileset.second.get<int>("firstgid");
                        if(tilesetGID <= id + 1)
                        { 
                            std::stringstream branch;
                            branch << "tileproperties." << id; 
                            boost::property_tree::ptree properties 
                                = tileset.second.get_child(branch.str());

                            std::string type = properties.get<std::string>("type");

                            //Prepare dialogueName for later
                            std::string dialogueName = properties.get<std::string>("dialogue","");

                            //Load specific entity propertyies
                            if(type=="player")
                            {
                                Player* p = new Player(j*_tileSize,i*_tileSize);
                                ent = p;
                            }
                            else if(type=="victim")
                            {
                                Victim* v = new Victim(j*_tileSize,i*_tileSize);

                                v->_part = properties.get<int>("part");

                                if(dialogueName != "")
                                {
                                    boost::property_tree::ptree dialogueTree;
                                    std::stringstream dialoguePath;
                                    std::stringstream resolvedPath;
                                    dialoguePath << "res/txt/" << dialogueName;

                                    resolvedPath << dialoguePath.str() << "2.xml";
                                    boost::property_tree::read_xml(resolvedPath.str(),
                                                                   dialogueTree);
                                    v->_dialogue2 = new DialogueTree(dialogueTree); 
                                }

                                ent = v;
                            }
                            else if(type=="warden")
                            {
                                Warden* w = new Warden(j*_tileSize,i*_tileSize);
                                ent = w;
                            }
                            else if(type=="table")
                            {
                                Table* t = new Table(j*_tileSize,i*_tileSize);
                                ent = t;
                            }
                            else if(type=="boss")
                            {
                                Boss* b = new Boss(j*_tileSize,i*_tileSize);
                                ent = b;
                            }
                            else
                            {
                                ent = new Entity(j*_tileSize,i*_tileSize);
                            }


                            //Load non-specific entity properties

                            if(dialogueName != "")
                            {
                                boost::property_tree::ptree dialogueTree;
                                std::stringstream dialoguePath;
                                dialoguePath << "res/txt/" << dialogueName << ".xml";
                                boost::property_tree::read_xml(dialoguePath.str(),
                                        dialogueTree);
                                ent->_dialogue = new DialogueTree(dialogueTree); 
                            }

                            ent->_type = type;
                            ent->_solid = properties.get<bool>("solid"); 
                            ent->_name = properties.get<std::string>("name","undefined");
                            std::string tilesetName = tileset.second.get<std::string>("name");
                            ent->setTexture( Graphics::getTexture(
                                    tilesetName,
                                    id - tilesetGID + 1));
                            ent->_tilesetName = tilesetName;
                            ent->_typeID = id;

                            break;
                        }
                    }

                    state->add(ent);
                }
            }
        }
    }
}
