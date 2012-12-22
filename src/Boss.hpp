#pragma once
#ifndef BOSS_H
#define BOSS_H

#include "Entity.hpp"

class Boss : public Entity
{
public:
    Boss(int x, int y);
    ~Boss();

    virtual void displayDialogue();
    virtual void setState(int i);
private:
    std::vector<DialogueTree*> _dTrees;
    int _stage;
};
#endif
