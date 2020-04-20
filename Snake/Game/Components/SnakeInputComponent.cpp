#include "Game/Components/SnakeInputComponent.hpp"

SnakeInputComponent::SnakeInputComponent(GameObject* gameObject) : InputComponent(gameObject) {
    this->addBinding(SDLK_UP, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_LEFT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_DOWN, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
}

void SnakeInputComponent::onMove(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: {
                inputVector.y() = -1;
                inputVector.x() = 0;
                break;
            }
            case SDLK_LEFT:
                inputVector.x() = -1;
                inputVector.y() = 0;
                break;
            case SDLK_DOWN: {
                inputVector.y() = 1;
                inputVector.x() = 0;
                break;
            }
            case SDLK_RIGHT: {
                inputVector.x() = 1;
                inputVector.y() = 0;
                break;
            }
        }
    }
}

bool SnakeInputComponent::isValidInput(Eigen::Vector2f directionVector) const {
    // Movement along the y-axis is restricted if already moving along the y-axis
    if((inputVector.y() == 1 || inputVector.y() == -1) && (directionVector.y() == 1 || directionVector.y() == -1)) {
        return false;
    }
    
    // Movement along the x-axis is restricted if already moving along the x-axis
    if((inputVector.x() == 1 || inputVector.y() == -1) && (directionVector.x() == 1 || directionVector.x() == -1)) {
        return false;
    }
    
    return true;
}
