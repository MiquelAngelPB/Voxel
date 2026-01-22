#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdbool.h>
#include "gl_manager.h"
#include "player.h"

//variables
bool quit = false;

//methods
void manageInput();

//main
int main() {
    glManager_Init();

    while (!quit)
    {
        manageInput();
        glManager_Render();
    }
    
    //SDL_Delay(3000);
    glManager_Clean();
}

void manageInput()
{
    float camDX = 0.0f;
    float camDY = 0.0f;
    float camDZ = 0.0f;

    float camDRX = 0.0f;
    float camDRY = 0.0f;
    float camDRZ = 0.0f;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_w)         { camDZ = -0.1f; }
                if (event.key.keysym.sym == SDLK_s)         { camDZ = 0.1f; }
                if (event.key.keysym.sym == SDLK_d)         { camDX = 0.1f; }
                if (event.key.keysym.sym == SDLK_a)         { camDX = -0.1f; }
                if (event.key.keysym.sym == SDLK_SPACE)     { camDY = 0.1f; }
                if (event.key.keysym.sym == SDLK_LSHIFT)    { camDY = -0.1f; }
    
                if (event.key.keysym.sym == SDLK_ESCAPE)    { SDL_SetRelativeMouseMode(SDL_FALSE);}
            break;
        
            case SDL_QUIT:
                quit = true;
            break;
        
            case SDL_MOUSEMOTION:
                camDRX = event.motion.xrel * 0.005f;
                camDRY = event.motion.yrel * 0.005f;
        }
    }

    moveCamera(camDX, camDY, camDZ);
    rotateCamera(camDRX, camDRY, camDRZ);
}