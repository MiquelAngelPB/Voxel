#include <SDL2/SDL.h>
#include <stdbool.h>

#include "platform/input.h"
#include "platform/gameState.h"

//variables
inputData input;
inputData* pInput;

//methods
void initInput()
{
    input = (inputData){
        .hasChanged = false,
        .keyMovement = {0, 0, 0},
        .mouseMovement = {0, 0}
    };

    pInput = &input;
}

void updateInput()
{
    input.hasChanged = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    *pGameState = STATE_STOP; //temporal
                }
                break;

            case SDL_QUIT:
                *pGameState = STATE_STOP;
                break;
        
            case SDL_MOUSEMOTION:
                input.hasChanged = true;
                input.mouseMovement.y += event.motion.xrel;
                input.mouseMovement.x += event.motion.yrel;
                break;
        }
    }

    int nKeys;
    const Uint8* keys = SDL_GetKeyboardState(&nKeys);

    if (nKeys)
    {
        input.hasChanged = true;
        if (keys[SDL_SCANCODE_W])         { input.keyMovement.z = 1; }
        if (keys[SDL_SCANCODE_S])         { input.keyMovement.z = -1; }

        if (keys[SDL_SCANCODE_D])         { input.keyMovement.x = 1; }
        if (keys[SDL_SCANCODE_A])         { input.keyMovement.x = -1; }

        if (keys[SDL_SCANCODE_SPACE])     { input.keyMovement.y = -1; }
        if (keys[SDL_SCANCODE_LSHIFT])    { input.keyMovement.y = 1; }
    }
}