#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "Keyboard.hpp"
#include "DialogueState.hpp"
#include "MainState.hpp"

sf::RenderWindow Game::window(sf::VideoMode(640, 480), "The Banker"); 
GameState* Game::currentState;
int Game::disguise = 0;
int Game::part = -1;
int Game::defacedTables = 0;
bool Game::running = false;

void Game::initialize()
{ 
    window.setFramerateLimit(60);
    Keyboard::initialize();
    currentState = new MainState();
}

void Game::run()
{
    sf::Event event;
    running = true;

    while(running)
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed: 
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }

        Keyboard::update();
        currentState->update();
        currentState->draw();

        window.display();
        window.clear();
    } 

    cleanUp();
}

void Game::end()
{
    running = false;
}

void Game::cleanUp()
{
    if(currentState)
    {
        delete currentState;
    }

    window.close();
}


void Game::displayDialogue(DialogueTree const* dTree, Entity* owner)
{
    DialogueState* dState = new DialogueState(currentState,owner,dTree);
    currentState = dState;
}

void Game::changeState(GameState* state)
{
    GameState* oldState = currentState;
    currentState = state;
    delete oldState;
}
