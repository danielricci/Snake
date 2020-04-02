#pragma once

#include "Game/Components/InputComponent.hpp"

#include <Eigen/Dense>

class SnakeInputComponent : public InputComponent {
public:
    SnakeInputComponent();
    inline Eigen::Vector2f getPositionVector() const {
        return positionVector;
    }
private:
    void onMove(const SDL_Event& event);
    
    const std::string ACTION_MOVE = "Move";
    
    Eigen::Vector2f positionVector { 1, 0 };
};
