#pragma once
#ifndef WARDEN_H
#define WARDEN_H

#include "Entity.hpp"

class Warden : public Entity
{
public:
    Warden(int x, int y);
    ~Warden();

    virtual void update();
    virtual void setState(int i);
    virtual void displayDialogue();
private:
    std::vector<DialogueTree*> _dTrees;
    sf::Vector2i _okayPos;
    sf::Vector2i _guardPos;

};
#endif
