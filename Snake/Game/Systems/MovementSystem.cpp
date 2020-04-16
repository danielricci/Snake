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

#include "Game/Components/CollisionComponent.hpp"
#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/SnakeInputComponent.hpp"
#include "Game/Systems/MovementSystem.hpp"

#include <Eigen/Dense>

#include <iostream>

void MovementSystem::process(SnakeObject* snakeObject, FoodObject* foodObject) {
    if(snakeObject != nullptr && foodObject != nullptr) {
        SnakeInputComponent* snakeInputComponent = snakeObject->getComponent<SnakeInputComponent>();
        if(snakeInputComponent != nullptr) {
            SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
            if(snakeBodyComponent != nullptr) {
                // Update the position of whats at the front with whats at the back plus the offset based on the current input
                snakeBodyComponent->snakeBody.front()->positionVector.x() = snakeBodyComponent->snakeBody.back()->positionVector.x() + (snakeInputComponent->getDirectionVector().x() * snakeBodyComponent->snakeBody.back()->dimensionVector.x());
                snakeBodyComponent->snakeBody.front()->positionVector.y() = snakeBodyComponent->snakeBody.back()->positionVector.y() + (snakeInputComponent->getDirectionVector().y() * snakeBodyComponent->snakeBody.back()->dimensionVector.y());
                
                // Position the front element to the back
                snakeBodyComponent->snakeBody.push_back(snakeBodyComponent->snakeBody.front());
                snakeBodyComponent->snakeBody.pop_front();
                
                // Verify if there is a collision with the head and the food
                if(snakeBodyComponent->snakeBody.back()->getWorldPositionVector() == foodObject->getComponent<TransformComponent>()->positionVector) {
                    std::cout << "Hit!!!" << std::endl;
                }
            }
        }
    }
}
