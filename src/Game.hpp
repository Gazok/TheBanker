#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "GameState.hpp"

class Game
{
public:
    static void initialize();
    static void run(); 
    static void end();
    static void cleanUp(); 

    static void displayDialogue(DialogueTree const* dTree, Entity* parent);
    static void changeState(GameState* state);
    static sf::RenderWindow window;
    static GameState* currentState;

    //Hooray global variables
    static int defacedTables;
    static int disguise;
    static int part;
private:
    static bool running;
    Game();
};
#endif
