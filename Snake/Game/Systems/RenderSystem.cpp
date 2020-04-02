/**
* MIT License
*
* Copyright (c) 2020 Daniel Ricci {@literal <thedanny09@icloud.com>}
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "Game/Components/RenderComponent.hpp"
#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/TransformComponent.hpp"
#include "Game/Systems/RenderSystem.hpp"

void RenderSystem::update(SDL_Renderer& renderer, GameObject* gameObject) {
    if(gameObject != nullptr) {
        RenderComponent* renderComponent = gameObject->getComponent<RenderComponent>();
        if(renderComponent != nullptr && renderComponent->isVisible) {
            SnakeBodyComponent* snakeBodyComponent = gameObject->getComponent<SnakeBodyComponent>();
            if(snakeBodyComponent != nullptr) {
                TransformComponent* gameObjectTransformComponent = gameObject->getComponent<TransformComponent>();
                SDL_SetRenderDrawColor(&renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
                for(int i = 0; i < snakeBodyComponent->snakeBody.size(); ++i) {
                    TransformComponent* snakeBodyTransform = snakeBodyComponent->snakeBody[i];
                    SDL_Rect rectangle;
                    rectangle.x = gameObjectTransformComponent->positionVector.x() + (snakeBodyTransform->positionVector.x() * snakeBodyTransform->dimensionVector.x());
                    rectangle.y = gameObjectTransformComponent->positionVector.y() + (snakeBodyTransform->positionVector.y() * snakeBodyTransform->dimensionVector.y());
                    rectangle.w = snakeBodyTransform->dimensionVector.x();
                    rectangle.h = snakeBodyTransform->dimensionVector.y();
                    
                    SDL_RenderFillRect(&renderer, &rectangle);
                }
            }
        }
    }
}
