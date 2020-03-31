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

#include "Game/GameObjects/SnakeObject.hpp"
#include "Game/GameWorld.hpp"
#include "Game/Managers/InputManager.hpp"

#include <iostream>

GameWorld::GameWorld(SDL_Renderer& renderer) : renderer(renderer) {
    InputManager::getInstance();
    gameObjects.push_back(new SnakeObject(300, 300));
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
    SDL_TimerID timerId = SDL_AddTimer(1000, [](Uint32 interval, void* param) -> Uint32 {
        SDL_UserEvent userevent;
        userevent.type = SDL_USEREVENT;
        userevent.code = 0;
        userevent.data1 = NULL;
        userevent.data2 = NULL;

        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user = userevent;

        SDL_PushEvent(&event);
        return interval;
    }, nullptr);

    // Run the game loop
    bool isGameQuit = false;
    while(!isGameQuit) {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_QUIT: {
                    SDL_RemoveTimer(timerId);
                    isGameQuit = true;
                    break;
                }
                case SDL_USEREVENT: {
                    //this->getGameObject<SnakeGameObject>()
                    break;
                }
            }
            
            // Handle any inputs
            InputManager::getInstance()->process(event, getGameComponents<SnakeObject, InputComponent>());
        }
        
        // Draw the contents of the game onto the screen
        SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(&renderer);
        for(GameObject* gameObject : gameObjects) {
            renderSystem->update(renderer, gameObject);
        }
        SDL_RenderPresent(&renderer);
    }
}
