#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(int x, int y);
    virtual void update();
private:
    bool _interacting;
    bool _moving;
    unsigned int _moved;

    void centreCamera();

    enum
    {
        Up,
        Left,
        Down,
        Right
    } _direction;
};
#endif
