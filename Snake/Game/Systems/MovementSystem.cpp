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
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

MovementSystem::MovementSystem(int width, int height) : width(width), height(height) {
}

void MovementSystem::process(SnakeObject* snakeObject, FoodObject* foodObject, GameOverObject* gameOverObject) {
    if(snakeObject != nullptr && foodObject != nullptr) {
        SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
                
        // Store a reference of the tail position before performing the move
        // and perform the movement of the snake by a unit
        Eigen::Vector2f tailPosition = snakeBodyComponent->getTail()->positionVector;
        snakeBodyComponent->moveTailToHead();

        // Test for collision with the outside of the game bounds
        Eigen::Vector2f headWorldPosition = snakeBodyComponent->getHead()->getWorldPositionVector();
        if(headWorldPosition.x() < 0 || headWorldPosition.y() < 0 || snakeBodyComponent->getHead()->positionVector.x() >= width || snakeBodyComponent->getHead()->positionVector.y() >= height) {
            gameOverObject->setIsGameOver(true);
        }
        // Test for collision with food
        else if(headWorldPosition == foodObject->getComponent<TransformComponent>()->positionVector) {
            snakeBodyComponent->increaseSnakeLength(tailPosition);
            processFoodPosition(snakeObject, foodObject);
        }
        // Test for collision with the snake body
        else {
            for(auto snakeBodyTailIterator = snakeBodyComponent->getTailIterator(); snakeBodyTailIterator < snakeBodyComponent->getHeadIterator(); ++snakeBodyTailIterator) {
                TransformComponent* transformComponent = *snakeBodyTailIterator;
                if(transformComponent != snakeBodyComponent->getHead() && transformComponent->getWorldPositionVector() == headWorldPosition) {
                    gameOverObject->setIsGameOver(true);
                    break;
                }
            }
        }
    }
}

void MovementSystem::processFoodPosition(SnakeObject* snakeObject, FoodObject* foodObject) {
    
    SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
            
    // Create the lists to hold all valid horizontal and vertical locations
    std::vector<int> horizontalLocations;
    std::vector<int> verticalLocations;

    // Fill both lists with values start at origin (0,0) outwards to width and downwards to height
    for(int i = 0; i < width; i += SnakeBodyComponent::CELL_WIDTH) {
        horizontalLocations.push_back(i);
    }
    for(int i = 0; i < height; i += SnakeBodyComponent::CELL_HEIGHT) {
        verticalLocations.push_back(i);
    }

    // Based on each x and y position of each snake body, remove that number from the horizonal and vertical location lists
    // After doing that, you are left with two lists that have values where the snake body is not located.
    for(auto snakeBodyTailIterator = snakeBodyComponent->getTailIterator(); *snakeBodyTailIterator != snakeBodyComponent->getHead(); ++snakeBodyTailIterator) {
        TransformComponent* transformComponent = *snakeBodyTailIterator;
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
    long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator((unsigned int)seed);
    int horizontalIndex = horizontalDistribution(generator);
    int verticalIndex = verticalDistribution(generator);
    foodObject->getComponent<TransformComponent>()->positionVector = Eigen::Vector2f { horizontalLocations[horizontalIndex], verticalLocations[verticalIndex] };
}
