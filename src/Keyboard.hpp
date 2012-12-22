#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Window/Keyboard.hpp>

class Keyboard
{
public:
    //Key has just been pressed
    static bool keyPressed(sf::Keyboard::Key key);
    //Key has just been released
    static bool keyReleased(sf::Keyboard::Key key);
    //Key is down
    static bool keyDown(sf::Keyboard::Key key);
    //Key is up
    static bool keyUp(sf::Keyboard::Key key);
private:
    static bool currentState[sf::Keyboard::Key::KeyCount];
    static bool lastState[sf::Keyboard::Key::KeyCount];

    friend class Game;
    static void update(); 
    static void initialize();
};

#endif
