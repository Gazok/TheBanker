#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "Entity.hpp"

class Table : public Entity
{
public:
    Table(int x, int y);
    ~Table();

    virtual void displayDialogue();
    virtual void setState(int i);
private:
    bool _defaced;
    std::vector<DialogueTree*> _dTrees;
};
#endif
