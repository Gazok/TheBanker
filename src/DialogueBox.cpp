#include "DialogueBox.hpp"

#include <sstream>
#include "Game.hpp"
#include "Keyboard.hpp"

sf::Font DialogueBox::_font;
sf::RectangleShape DialogueBox::_box;
bool DialogueBox::_initialized = false;

DialogueBox::DialogueBox(DialogueTree const* dTree,
                         Entity* owner,
                         DialogueState* dState)
    : Entity(sf::Vector2i()), _dialogueState(dState)
{
    const int borderSize = 3;
    const int boxHeight = 100;

    if(!_initialized)
    {
        _box.setSize(sf::Vector2f(Game::window.getSize().x - 2*borderSize,
                                  boxHeight)); 
        _box.setFillColor(sf::Color(0,50,200));
        _box.setOutlineColor(sf::Color(0,25,100));
        _box.setOutlineThickness(borderSize);
        _font.loadFromFile("res/fnt/LibMono.ttf");

        _initialized = true;
    }

    _pos = sf::Vector2i(borderSize,
                        Game::window.getSize().y - borderSize - boxHeight);

    sf::Vector2f _topLeft = Game::window.getView().getCenter();
    _topLeft.x -=  Game::window.getSize().x / 2.0f;
    _topLeft.y -=  Game::window.getSize().y / 2.0f;

    _pos.x += _topLeft.x;
    _pos.y += _topLeft.y;

    _box.setPosition(_pos.x,_pos.y);
    _currentText.setFont(_font);
    _currentText.setPosition(_pos.x + 10,_pos.y);
    _currentText.setCharacterSize(10);

    _owner = owner;

    loadFromTree(dTree);
}

void DialogueBox::update()
{ 
    if(Keyboard::keyPressed(sf::Keyboard::Key::Space))
    {
        if(!_textLines.empty())
        {
            _currentText.setString(_textLines.front());
            _textLines.pop_front();
        }
        else if(!_currentTree->getOptions().empty())
        {
            if(!_displayingOptions)
            {
                _displayingOptions = true; 
                loadOptions();
            }
        }
        else
        {
            _owner->setState(_lastOption);
            _dialogueState->finished(); 
        }
    }
    if(_displayingOptions)
    {
        if(Keyboard::keyPressed(sf::Keyboard::Key::Num1))
        {
            _currentOption = 1;
        }
        else if(Keyboard::keyPressed(sf::Keyboard::Key::Num2))
        {
            _currentOption = 2;
        }
        else if(Keyboard::keyPressed(sf::Keyboard::Key::Num3))
        {
            _currentOption = 3;
        }
        if(_currentOption != 0 && _currentOption - 1 < _currentTree->getOptions().size())
        {
            _lastOption = _currentOption;
            loadFromTree(_currentTree->chooseOption(_currentOption - 1)); 
        } 
    }
}

void DialogueBox::draw()
{ 
    if(_visible)
    { 
        Game::window.draw(_box);
        Game::window.draw(_currentText);
    }
}

void DialogueBox::loadFromTree(DialogueTree const* dTree)
{
    _currentTree = dTree;

    _displayingOptions = false; 
    _currentOption = 0;
    
    unsigned int numLines = _currentTree->getText().size();
    for(unsigned int i = 0; i < numLines; ++i)
    {
        std::stringstream s; 
        s << _owner->getName() << "\n\n";
        s << _currentTree->getText()[i];

        _textLines.push_back(s.str());
    }
    _currentText.setString(_textLines.front());
    _textLines.pop_front(); 
}

void DialogueBox::loadOptions()
{
    std::stringstream s;
    std::vector<std::string> const& options = _currentTree->getOptions();

    _currentOption = 0;
    unsigned int numOptions = options.size();

    s << _owner->getName() << "\n\n";
    for(unsigned int i = 0; i < numOptions; ++i)
    {
        s << " " << i+1 << ". " << options[i] << "\n\n";
    }

    _currentText.setString(s.str());
}
