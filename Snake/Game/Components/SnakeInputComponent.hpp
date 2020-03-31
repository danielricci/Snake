#pragma once

#include "Game/Components/InputComponent.hpp"

class SnakeInputComponent : public InputComponent {
public:
    SnakeInputComponent();
private:
    void onMove(const SDL_Event& event);
    
    const std::string ACTION_MOVE = "Move";
    
    int directionX = 1;
    int directionY = 0;
};
