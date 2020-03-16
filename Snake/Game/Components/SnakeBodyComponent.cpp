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

#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/TransformComponent.hpp"

SnakeBodyComponent::SnakeBodyComponent(int size) {
    this->addComponent(new TransformComponent(0, 0, WIDTH, HEIGHT));
    
    SnakeBodyComponent* snakeBodyComponent = this;
    for(int i = 0; i < size - 1; ++i) {
        TransformComponent* transformComponent = snakeBodyComponent->getComponent<TransformComponent>();
        SnakeBodyComponent* nextSnakeBodyComponent = new SnakeBodyComponent(transformComponent->positionVector.x() + WIDTH - 1, transformComponent->positionVector.y());
        snakeBodyComponent->addComponent(nextSnakeBodyComponent);
        snakeBodyComponent = nextSnakeBodyComponent;
    }
}

SnakeBodyComponent::SnakeBodyComponent(int x, int y) {
    this->addComponent(new TransformComponent(x, y, WIDTH, HEIGHT));
}

void SnakeBodyComponent::grow() {
    // TODO - this needs to be done w.r.t when the snake actually eats
//    SnakeBodyComponent* snakeBodyComponent = this;
//    while(snakeBodyComponent->getComponent<SnakeBodyComponent>() != nullptr) {
//        snakeBodyComponent = snakeBodyComponent->getComponent<SnakeBodyComponent>();
//    }
//
//    TransformComponent* transformComponent = snakeBodyComponent->getComponent<TransformComponent>();
//    snakeBodyComponent->addComponent(new SnakeBodyComponent(transformComponent->positionVector.x() + WIDTH - 1, transformComponent->positionVector.y()));
}
