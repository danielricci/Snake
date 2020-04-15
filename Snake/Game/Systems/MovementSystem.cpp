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
                // Get a reference to the current last component
                TransformComponent* lastComponent = snakeBodyComponent->snakeBody.back();
                
                // Update the first element with a new set of coordinates
                snakeBodyComponent->snakeBody.front()->positionVector = snakeInputComponent->getPositionVector() + lastComponent->positionVector;
                
                // Move the front element to the end of the list
                snakeBodyComponent->snakeBody.push_back(snakeBodyComponent->snakeBody.front());
                snakeBodyComponent->snakeBody.pop_front();
                
                if(snakeBodyComponent->getHead()->positionVector == foodObject->getComponent<TransformComponent>()->positionVector) {
                    std::cout << "HIT!" << std::endl;
                }
            }
        }
    }
}

//void MovementSystem::processSnakeCollision(const SnakeObject& snakeObject) {
//    for(GameObject* gameObject : this->gameObjects) {
//        if(gameObject != &snakeObject) {
//            CollisionComponent* collisionComponent = gameObject->getComponent<CollisionComponent>();
//            if(collisionComponent != nullptr && collisionComponent->isCollidedAABB(snakeObject)) {
//
//            }
//        }
//    }
//}
