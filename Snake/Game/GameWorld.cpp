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

#include "Game/GameObjects/FoodObject.hpp"
#include "Game/GameObjects/SnakeObject.hpp"
#include "Game/GameWorld.hpp"
#include "Game/Managers/InputManager.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : renderer(renderer) {
    // TODO initialization should be done better than this...
    InputManager::getInstance();

    renderSystem = new RenderSystem(renderer);
    
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(&window, &width, &height);
    movementSystem = new MovementSystem(width, height);
    
    // Create the Snake Object
    SnakeObject* snakeObject = new SnakeObject(306, 306);
    gameObjects.push_back(snakeObject);
    
    // Create the Food Object
    Eigen::Vector2i unitSize = snakeObject->getComponent<SnakeBodyComponent>()->getUnitSize();
    FoodObject* foodObject = new FoodObject(72, 72, unitSize.x(), unitSize.y());
    gameObjects.push_back(foodObject);
}

GameWorld::~GameWorld() {
    // Handle the managers
    InputManager::getInstance()->terminate();

    // Handle the render system
    delete renderSystem;
    renderSystem = nullptr;
    
    // Handle the game objects
    for(GameObject* gameObject : gameObjects) {
        delete gameObject;
        gameObject = nullptr;
    }
    gameObjects.clear();
}

void GameWorld::run() {
    
    // Create a timer that will push a user event to indicate that `something special` should occur
    SDL_TimerID timerId = SDL_AddTimer(tickSpeed, [](Uint32 interval, void* param) -> Uint32 {
        SDL_UserEvent userevent;
        userevent.type = SDL_USEREVENT;
        userevent.code = 0;
        userevent.data1 = NULL;
        userevent.data2 = NULL;

        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user = userevent;

        SDL_PushEvent(&event);
        
        GameWorld* gameWorld = static_cast<GameWorld*>(param);
        return gameWorld->tickSpeed;
    }, this);

    // Run the game loop
    bool isGameQuit = false;
    while(!isGameQuit) {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {

            // Handle the quit event
            if(event.type == SDL_QUIT) {
                SDL_RemoveTimer(timerId);
                isGameQuit = true;
                break;
            }
            
            // Handle the speed of the snake. For now this is done through F1 (decrease) and F2 (increase) speed options
            if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_F1) {
                int newSpeed = this->tickSpeed - 100;
                if(newSpeed >= 100) {
                    this->tickSpeed = newSpeed;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_F2) {
                int newSpeed = this->tickSpeed + 100;
                if(newSpeed <= 1000) {
                    this->tickSpeed = newSpeed;
                }
            }
            
            // Process any inputs
            InputManager::getInstance()->process(event, getGameComponents<SnakeObject, InputComponent>());
            
            // Handle the user event
            if(event.type == SDL_USEREVENT) {
                // Movement System
                movementSystem->process(this->getGameObject<SnakeObject>(), this->getGameObject<FoodObject>());
                
                // Clear the back buffer to prepare it for rendering
                SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(&renderer);
                
                // Render System
                renderSystem->process(gameObjects);
                
                // Blit everything onto the display
                SDL_RenderPresent(&renderer);
            }
        }
    }
}
