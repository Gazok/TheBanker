#pragma once
#ifndef DIALOGUESTATE_H
#define DIALOGUESTATE_H

#include "GameState.hpp"

class DialogueState : public GameState
{
public:
    DialogueState(GameState* parentState,
                  Entity* parent,
                  DialogueTree const* dTree);
    void finished();
    virtual void draw();
private:
    GameState* _parentState;
};
#endif
