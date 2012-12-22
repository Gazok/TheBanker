#pragma once
#ifndef VICTIM_H
#define VICTIM_H

#include "Entity.hpp"

class Victim : public Entity
{
public:
    Victim(int x, int y);
    ~Victim();

    void update();
    void displayDialogue();
    void setState(int i);
private:
    bool _victimized;
    DialogueTree* _dialogue2;
    int _part;
    bool _removed;

    friend class Map;
};
#endif
