#include <SDL2/SDL.h>
#include <stdbool.h>
#include "input.h" //includes itself to use quit variable (temporary)
#include "camera.h"

//variables
float sensitivity = 0.00078539816 * 2; //(2.0f * M_PI) / 800.0f;

//methods
void manageInput()
{
    float camDX = 0.0f, camDY = 0.0f, camDZ = 0.0f;
    float camDRX = 0.0f, camDRY = 0.0f, camDRZ = 0.0f;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    quit = true;
                }
                break;

            case SDL_QUIT:
                quit = true;
                break;
        
            case SDL_MOUSEMOTION:
                camDRY += event.motion.xrel * sensitivity;
                camDRX += event.motion.yrel * sensitivity;
                break;
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);  

    if (keys[SDL_SCANCODE_W])         { camDZ = 1; }
    if (keys[SDL_SCANCODE_S])         { camDZ = -1; }
    if (keys[SDL_SCANCODE_D])         { camDX = 1; }
    if (keys[SDL_SCANCODE_A])         { camDX = -1; }

    if (keys[SDL_SCANCODE_SPACE])     { camDY = -1; }
    if (keys[SDL_SCANCODE_LSHIFT])    { camDY = 1; }

    pushCamera(camDX, camDY, camDZ);
    rotateCamera(camDRX, camDRY, camDRZ);
}