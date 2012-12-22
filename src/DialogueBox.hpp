#pragma once
#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Entity.hpp"
#include "DialogueState.hpp"
#include "DialogueTree.hpp"
#include <deque>

class DialogueBox : public Entity
{
public:
    DialogueBox(DialogueTree const*, Entity* owner, DialogueState* dState);

    void update();
    void draw();
private:
    DialogueTree const* _currentTree;
    sf::Text _currentText;
    std::deque<std::string> _textLines;
    unsigned int _currentOption;
    unsigned int _lastOption;
    bool _displayingOptions;
    Entity* _owner;

    DialogueState* _dialogueState;

    static sf::RectangleShape _box;
    static sf::Font _font;
    static bool _initialized;
    static int _charSize;

    void loadFromTree(DialogueTree const*);
    void loadOptions();
};
#endif
