#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdbool.h>
#include "gl_manager.h"

//variables
bool quit = false;
float camX = 0.0f;
float camY = 0.0f;
float camZ = -3.0f;

//methods

//main
int main() {
    glManager_Init();

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_DOWN)  { camZ -= 0.1f; }
                    if (event.key.keysym.sym == SDLK_UP)    { camZ += 0.1f; }
                break;

                case SDL_QUIT:
                    quit = true;
                break;
            }
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        glManager_Render(camX, camY, camZ, mouseX, mouseY); //TODO: Refactor this.
    }
    
    //SDL_Delay(3000);
    glManager_Clean();
}