#include "Game/Components/SnakeInputComponent.hpp"

SnakeInputComponent::SnakeInputComponent() {
    this->addBinding(SDLK_UP, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_LEFT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_DOWN, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
}

void SnakeInputComponent::onMove(const SDL_Event& event) {
    if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: {
                if(directionY != 1) {
                    directionY = -1;
                    directionX = 0;
                }
                break;
            }
            case SDLK_LEFT:
                if(directionX != 1) {
                    directionX = -1;
                    directionY = 0;
                }
                break;
            case SDLK_DOWN: {
                if(directionY != -1) {
                    directionY = 1;
                    directionX = 0;
                }
                break;
            }
            case SDLK_RIGHT: {
                if(directionX != -1) {
                    directionX = 1;
                    directionY = 0;
                }
                break;
            }
        }
    }
}
