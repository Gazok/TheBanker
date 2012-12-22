#include "Player.hpp"

#include "Keyboard.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "Graphics.hpp"

//remove
#include <iostream>

Player::Player(int x, int y) : Entity(x,y) 
{
    _direction = Left;
    _moving = false;
    _moved = 0;
    _interacting = false;

    Graphics::loadTilemap("res/gfx/player.png","player",32);
}

void Player::update()
{ 
    switch(_direction)
    {
        case Up:
            _sprite.setTexture(Graphics::getTexture("player",Game::disguise*4 + 0));
            break;
        case Right:
            _sprite.setTexture(Graphics::getTexture("player",Game::disguise*4 + 1));
            break;
        case Down:
            _sprite.setTexture(Graphics::getTexture("player",Game::disguise*4 + 2));
            break;
        case Left:
            _sprite.setTexture(Graphics::getTexture("player",Game::disguise*4 + 3));
            break;
    }

    if(!_moving)
    {
        if(Keyboard::keyDown(sf::Keyboard::Key::W)
        || Keyboard::keyDown(sf::Keyboard::Key::Up))
        {
            _direction = Up;
            _moving = true;
        } 
        else if(Keyboard::keyDown(sf::Keyboard::Key::D)
        || Keyboard::keyDown(sf::Keyboard::Key::Right))
        {
            _direction = Right;
            _moving = true;
        } 
        else if(Keyboard::keyDown(sf::Keyboard::Key::S)
        || Keyboard::keyDown(sf::Keyboard::Key::Down))
        {
            _direction = Down;
            _moving = true;
        } 
        else if(Keyboard::keyDown(sf::Keyboard::Key::A)
        || Keyboard::keyDown(sf::Keyboard::Key::Left))
        {
            _direction = Left;
            _moving = true;
        } 
        else if(Keyboard::keyPressed(sf::Keyboard::Key::Return)
        || Keyboard::keyPressed(sf::Keyboard::Key::Space))
        {
            _interacting = true;
        }

        if(_moving || _interacting)
        {
            int x = 0;
            int y = 0;
            int width = _hitbox.width;
            switch(_direction)
            {
                case Left:  x = -width; break;
                case Right: x =  width; break;
                case Up:    y = -width; break;
                case Down:  y =  width; break;
            }

            std::vector<Entity*> collisions = 
                _gameState->collide(this,sf::Vector2i(x,y));

            if(_moving)
            {
                while(!collisions.empty())
                {
                    if(collisions.back()->isSolid())
                    {
                        _moving = false;
                    }
                    collisions.pop_back();
                }
            }
            else if(_interacting)
            {
                while(!collisions.empty())
                {
                    collisions.back()->interact();
                    collisions.pop_back();
                }
                _interacting = false;
            }
        } 
    }
    else
    {
        if(_moved*2 < _sprite.getTextureRect().width)
        {
            ++_moved;
            int x = 0;
            int y = 0;
            switch(_direction)
            {
                case Left:  _pos.x -= 2; break;
                case Right: _pos.x += 2; break;
                case Up:    _pos.y -= 2; break;
                case Down:  _pos.y += 2; break;
            }

            _pos.x += x;
            _pos.y += y;

            _sprite.setPosition(_pos.x,_pos.y);
            _hitbox.left = _pos.x;
            _hitbox.top  = _pos.y;
        }
        else
        {
           _moving = false;
           _moved = 0; 
        }
    }

    centreCamera(); 
}

void Player::centreCamera()
{
        sf::View view = Game::window.getView();
        float x = _sprite.getPosition().x + _hitbox.width / 2;
        float y = _sprite.getPosition().y + _hitbox.width / 2;

        view.setCenter(x,y);
        Game::window.setView(view); 
} 
