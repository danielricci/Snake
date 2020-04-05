#include "Game/Components/SnakeInputComponent.hpp"

SnakeInputComponent::SnakeInputComponent() {
    this->addBinding(SDLK_UP, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_LEFT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_DOWN, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
}

void SnakeInputComponent::onMove(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: {
                if(positionVector.y() != 1) {
                    positionVector.y() = -1;
                    positionVector.x() = 0;
                }
                break;
            }
            case SDLK_LEFT:
                if(positionVector.x() != 1) {
                    positionVector.x() = -1;
                    positionVector.y() = 0;
                }
                break;
            case SDLK_DOWN: {
                if(positionVector.y() != -1) {
                    positionVector.y() = 1;
                    positionVector.x() = 0;
                }
                break;
            }
            case SDLK_RIGHT: {
                if(positionVector.x() != -1) {
                    positionVector.x() = 1;
                    positionVector.y() = 0;
                }
                break;
            }
        }
    }
}
