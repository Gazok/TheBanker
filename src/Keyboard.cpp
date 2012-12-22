#include "Keyboard.hpp"
#include <algorithm>

bool Keyboard::currentState[sf::Keyboard::Key::KeyCount];
bool Keyboard::lastState[sf::Keyboard::Key::KeyCount];

void Keyboard::initialize()
{
    std::fill(currentState,currentState + sf::Keyboard::Key::KeyCount, false);
}

void Keyboard::update()
{
    for(int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
    {
        lastState[i] = currentState[i]; 
        currentState[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
    }
}

bool Keyboard::keyPressed(sf::Keyboard::Key key)
{ 
    return currentState[key] && !lastState[key];
}

bool Keyboard::keyReleased(sf::Keyboard::Key key)
{
    return !currentState[key] && lastState[key];
}

bool Keyboard::keyDown(sf::Keyboard::Key key) { return currentState[key]; }
bool Keyboard::keyUp(sf::Keyboard::Key key) { return !currentState[key]; }
