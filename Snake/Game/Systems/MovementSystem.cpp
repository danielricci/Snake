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

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

MovementSystem::MovementSystem(int width, int height) : width(width), height(height) {
}

void MovementSystem::process(SnakeObject* snakeObject, FoodObject* foodObject) {
    if(snakeObject != nullptr && foodObject != nullptr) {
        SnakeInputComponent* snakeInputComponent = snakeObject->getComponent<SnakeInputComponent>();
        if(snakeInputComponent != nullptr) {
            SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
            if(snakeBodyComponent != nullptr) {
                snakeBodyComponent->moveTailToHead();

                
                // TODO - Get World position!
//                if(snakeBodyComponent->snakeBody.back()->getWorldPositionVector() == foodObject->getComponent<TransformComponent>()->positionVector) {
//
//                }
                
                /*
                // Hold onto a reference of the front of the snake.
                Eigen::Vector2f snakeBodyFront = snakeBodyComponent->getTail();

                // Test for collision with the outside of the game bounds
                Eigen::Vector2f headSnakeWorldPosition = snakeBodyComponent->getHead()->getWorldPositionVector();
                if(headSnakeWorldPosition.x() < 0 || headSnakeWorldPosition.y() < 0 || snakeBodyComponent->getHead().x() >= width || snakeBodyComponent->getHead().y() >= height) {
                    
                }
                // Test for collision with food
                else if(snakeBodyComponent->snakeBody.back()->getWorldPositionVector() == foodObject->getComponent<TransformComponent>()->positionVector) {
                    snakeBodyComponent->snakeBody.push_front(new TransformComponent(snakeBodyComponent->getGameObject(), snakeBodyFront.x, snakeBodyFront.y, snakeBodyFront.w, snakeBodyFront.h));
                    
                    // Create the lists to hold all valid horizontal and vertical locations
                    std::vector<int> horizontalLocations;
                    std::vector<int> verticalLocations;
                    
                    // Fill both lists with values start at origin (0,0) outwards to width and downwards to height
                    Eigen::Vector2i unitSize = snakeBodyComponent->getUnitSize();
                    for(int i = 0; i < width; i += unitSize.x()) {
                        horizontalLocations.push_back(i);
                    }
                    for(int i = 0; i < height; i += unitSize.y()) {
                        verticalLocations.push_back(i);
                    }
                                        
                    // Based on each x and y position of each snake body, remove that number from the horizonal and vertical location lists
                    // After doing that, you are left with two lists that have values where the snake body is not located.
                    for(TransformComponent* transformComponent : snakeBodyComponent->snakeBody) {
                        std::vector<int>::iterator horizontalIndexIterator = std::find(horizontalLocations.begin(), horizontalLocations.end(), transformComponent->getWorldPositionVector().x());
                        if(horizontalIndexIterator != horizontalLocations.end()) {
                            horizontalLocations.erase(horizontalIndexIterator);
                        }
                        std::vector<int>::iterator verticalIndexIterator = std::find(verticalLocations.begin(), verticalLocations.end(), transformComponent->getWorldPositionVector().y());
                        if(verticalIndexIterator != verticalLocations.end()) {
                            verticalLocations.erase(verticalIndexIterator);
                        }
                    }
                    
                    // Pick a random horizontal and vertical location and set the food object to that position
                    std::uniform_int_distribution<int> horizontalDistribution(0, static_cast<int>(horizontalLocations.size() - 1));
                    std::uniform_int_distribution<int> verticalDistribution(0, static_cast<int>(verticalLocations.size() - 1));
                    std::mt19937 generator(static_cast<std::mt19937::result_type>(std::time(nullptr)));
                    int horizontalIndex = horizontalDistribution(generator);
                    int verticalIndex = verticalDistribution(generator);
                    foodObject->getComponent<TransformComponent>()->positionVector = Eigen::Vector2f { horizontalLocations[horizontalIndex], verticalLocations[verticalIndex] };
                }
                // Test for collision with the snake body
                else if(snakeBodyComponent->snakeBody.size() > 1) {
                    // Note: Loop requires condition that there be at least 2 elements
                    Eigen::Vector2f headWorldPosition = snakeBodyComponent->snakeBody.back()->getWorldPositionVector();
                    for(int i = 0; i < snakeBodyComponent->snakeBody.size() - 1; ++i) {
                        if(snakeBodyComponent->snakeBody[i]->getWorldPositionVector() == headWorldPosition) {
                            break;
                        }
                    }
                }
                 
                 */
            }
        }
    }
}
