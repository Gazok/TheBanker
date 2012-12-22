#include "DialogueState.hpp"
#include "DialogueBox.hpp"
#include "Game.hpp"

DialogueState::DialogueState(GameState* parentState,
                             Entity* dParent,
                             DialogueTree const* dTree)
    : _parentState(parentState)
{
    add(new DialogueBox(dTree,dParent,this));
}

void DialogueState::draw()
{
    _parentState->draw();
    GameState::draw();
}

void DialogueState::finished()
{
    Game::changeState(_parentState);
}
